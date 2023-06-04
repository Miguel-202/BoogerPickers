// Fill out your copyright notice in the Description page of Project Settings.


#include "TheRizzrdAvatar.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AnimationInstance/RizzardAnim.h"
#include "Components/HealthComponent.h"
#include "Components/EffectComponent.h"

// Sets default values
ATheRizzrdAvatar::ATheRizzrdAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	EffectComponent = CreateDefaultSubobject<UEffectComponent>(TEXT("EffectComponent"));
	
}

// Called when the game starts or when spawned
void ATheRizzrdAvatar::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDamaged.AddDynamic(this, &ATheRizzrdAvatar::AvatarDamaged);
	HealthComponent->OnDeath.AddDynamic(this, &ATheRizzrdAvatar::AvatarDeath);
	EffectComponent->OnFireIceCombo.AddDynamic(this, &ATheRizzrdAvatar::OnFireIceCombo);
}

void ATheRizzrdAvatar::OnFireIceCombo_Implementation()
{
}
