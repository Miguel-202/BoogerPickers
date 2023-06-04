// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheRizzardCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/TimelineComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/ChildActorComponent.h"
#include "Actors/BaseSpellCast.h"
#include "AnimationInstance/RizzardAnim.h"
#include "Components/HealthComponent.h"
#include "Components/ManaComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "Widgets/PlayerHUD.h"

//////////////////////////////////////////////////////////////////////////
// ATheRizzardCharacter

ATheRizzardCharacter::ATheRizzardCharacter()
{

	PrimaryActorTick.bCanEverTick = false;
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	ManaComponent = CreateDefaultSubobject<UManaComponent>(TEXT("ManaComponent"));
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// Create a Spell-casting child actor that shoots spell
	Mesh = GetMesh();
	CastComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("CastComponent"));
	CastComponent->SetupAttachment(Mesh);
	CastComponent->AttachToComponent(CastComponent->GetAttachParent(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("LeftHandCast")));

	//Dash variables
	_dashDistance = 1500.f;
	_dashCooldown = 0.78f;
	_dashSpeed = 1500.f;
	_isDashing = false;
	_isLevitating = false;
}

void ATheRizzardCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Setting the CastComponent actor Class
	CastComponent->SetChildActorClass(SpellCastClass);
	// Getting the CastComponent object reference
	CastFocus = Cast<ABaseSpellCast>(CastComponent->GetChildActor());

	//Add Input Mapping Context
	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Binding Sync between Weapon functions and animations.
	AnimBP = Cast<URizzardAnim>(Mesh->GetAnimInstance());
	BindWeaponAndAnimEvents();

	//Create HUD, attach to player
	PlayerHUD = CreateWidget<UPlayerHUD>(PlayerController, HUDClass);
	PlayerHUD->AddToPlayerScreen();

	BindHUDAndStatComponentEvents();

}

void ATheRizzardCharacter::Dash()
{
	if (_isDashing)
	{
		return;
	}

	// Get the rotation of the controller
	FRotator ControllerRotation = GetControlRotation();

	FVector dashDirection = ControllerRotation.Vector().GetSafeNormal();

	// Calculate the end location of the dash
	FVector dashEndLocation = GetActorLocation() + (dashDirection * _dashDistance);

	// Set the character movement mode to flying during the dash
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	_isDashing = true;

	LaunchCharacter(dashDirection * _dashSpeed, true, true);

	//instantiate niagara particle system _dashParticle
	if (_dashParticle != nullptr)
	{
		UNiagaraComponent* niagaraComponent = NewObject<UNiagaraComponent>(this);
		niagaraComponent->SetAsset(_dashParticle);
		niagaraComponent->SetWorldLocation(GetActorLocation() - FVector(0,0, 100));
		niagaraComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
		niagaraComponent->SetWorldRotation(dashDirection.Rotation());
		niagaraComponent->SetAutoDestroy(true);
		niagaraComponent->RegisterComponent();
	}
	FollowCamera->SetFieldOfView(100);



}

void ATheRizzardCharacter::Levitate()
{
	if (GetCharacterMovement()->IsFalling())
	{
		_isLevitating = true;
		// Disable gravity for the character
		GetCharacterMovement()->GravityScale = 0.3f;
		
		// Make timer so it doesn't float forever
		GetWorld()->GetTimerManager().SetTimer(LevitateTimer, this, &ATheRizzardCharacter::StopLevitate, 2, false);

		
		if (_levitateParticle != nullptr)
		{
			UNiagaraComponent* niagaraComponent = NewObject<UNiagaraComponent>(this);
			niagaraComponent->SetAsset(_levitateParticle);
			niagaraComponent->SetWorldLocation(GetActorLocation() - FVector(0, 0, 100));
			niagaraComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
			niagaraComponent->SetWorldRotation(GetActorForwardVector().GetSafeNormal().Rotation());
			niagaraComponent->SetAutoDestroy(true);
			niagaraComponent->RegisterComponent();
		}
		FollowCamera->SetFieldOfView(100);
	}
	

}

void ATheRizzardCharacter::StopLevitate()
{
	_isLevitating = false;
	// Enable gravity for the character
	GetCharacterMovement()->GravityScale = 1.8f;
	GetWorld()->GetTimerManager().ClearTimer(LevitateTimer);
	FollowCamera->SetFieldOfView(90);

}

void ATheRizzardCharacter::StopDash()
{
	// Set the character movement mode back to walking after the dash
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	_isDashing = false;
	FollowCamera->SetFieldOfView(90);
}


//////////////////////////////////////////////////////////////////////////
// Input

void ATheRizzardCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATheRizzardCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATheRizzardCharacter::Look);

		//Dashing
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ATheRizzardCharacter::Dash);

		//Spellcasting
		EnhancedInputComponent->BindAction(CastAction, ETriggerEvent::Triggered, this, &ATheRizzardCharacter::CastInput);

		//Spell Cycling

		EnhancedInputComponent->BindAction(SpellCycleAction, ETriggerEvent::Triggered, this, &ATheRizzardCharacter::SpellCycle);
		
		//Levitate
		//EnhancedInputComponent->BindAction(LevitateAction, ETriggerEvent::Triggered, this, &ATheRizzardCharacter::Levitate);
		PlayerInputComponent->BindAction("Levitate", EInputEvent::IE_Pressed, this, &ATheRizzardCharacter::Levitate);
		PlayerInputComponent->BindAction("Levitate", EInputEvent::IE_Released, this, &ATheRizzardCharacter::StopLevitate);



	}

}

void ATheRizzardCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATheRizzardCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATheRizzardCharacter::SpellCycle(const FInputActionValue& Value) {
	
	// input is a float, sign signifies which way.
	CastFocus->ChangeActiveSpell(Value.Get<float>());
	
}

void ATheRizzardCharacter::CastInput() {
		CastFocus->CastSpell(ManaComponent->GetMana());
}

void ATheRizzardCharacter::BindWeaponAndAnimEvents() {
	AnimBP->OnAnimComplete.AddDynamic(this, &ATheRizzardCharacter::BindToOnAnimComplete);
	AnimBP->OnSpawnSpell.AddDynamic(this, &ATheRizzardCharacter::BindToOnSpawnSpell);
	CastFocus->OnCast.AddDynamic(this, &ATheRizzardCharacter::BindToOnCast);
	CastFocus->OnSpellChange.AddDynamic(this, &ATheRizzardCharacter::BindToOnSpellChange);
}

void ATheRizzardCharacter::BindHUDAndStatComponentEvents() {
	HealthComponent->OnDamaged.AddDynamic(this, &ATheRizzardCharacter::BindToOnDamaged);
	ManaComponent->OnManaUsed.AddDynamic(this, &ATheRizzardCharacter::BindToOnManaUsed);
}

void ATheRizzardCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	//do once Launch character to dash end location with delay of 0.1 seconds
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ATheRizzardCharacter::StopDash, _dashCooldown, false);
}

void ATheRizzardCharacter::BindToOnAnimComplete() {
	CastFocus->AnimationComplete();
}

void ATheRizzardCharacter::BindToOnSpawnSpell() {
	CastFocus->SpawnSpell();
}

void ATheRizzardCharacter::BindToOnCast(float _manaCost) {
	AnimBP->PlayCastAnimation();
	ManaComponent->SetMana(_manaCost);
}

void ATheRizzardCharacter::BindToOnSpellChange(UAnimSequenceBase* CastAsset, float ScrollDirection) {
	AnimBP->SetCastAsset(CastAsset);
	PlayerHUD->SetOffset(ScrollDirection);
}

void ATheRizzardCharacter::BindToOnDamaged(float _ratio) {
	PlayerHUD->SetHealth(_ratio);
}

void ATheRizzardCharacter::BindToOnManaUsed(float _ratio) {
	PlayerHUD->SetMana(_ratio);
}

void ATheRizzardCharacter::AvatarDamaged(float _ratio) {
	AnimBP->PlayHurtAnimation();
}

void ATheRizzardCharacter::AvatarDeath(float _ratio) {
	DisableInput(PlayerController);
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->StopMovementImmediately();
	Movement->DisableMovement();
	PlayerHUD->RemoveFromParent();
	UCapsuleComponent* CollisionComp = GetCapsuleComponent();
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CastFocus->Corpse();
	Mesh->SetCollisionProfileName(FName(TEXT("Ragdoll")));
	Mesh->SetSimulatePhysics(true);
}