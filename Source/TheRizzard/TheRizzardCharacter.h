// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TheRizzrdAvatar.h"
#include "InputActionValue.h"
#include "TheRizzardCharacter.generated.h"


UCLASS(config=Game)
class ATheRizzardCharacter : public ATheRizzrdAvatar
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* CastComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UManaComponent* ManaComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABaseSpellCast> SpellCastClass;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DashAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LevitateAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CastAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SpellCycleAction;

public:
	ATheRizzardCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for Spell Cycling input */
	UFUNCTION()
	void SpellCycle(const FInputActionValue& Value);

	//Dash variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float _dashDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float _dashCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float _dashSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dash")
	bool _isDashing;

	bool _isLevitating;
	FTimerHandle LevitateTimer;
	//Dash niagara particle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	class UNiagaraSystem* _dashParticle;
	//Dash niagara particle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	class UNiagaraSystem* _levitateParticle;
	// Spell Casting Actor reference.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABaseSpellCast* CastFocus;
	// Explanation for this: ACharacter has a 'Mesh' variable. UPROPERTY makes this visible in the reflection system. Take out the UPROPERTY specifier, and Unreal no longer sees it.
	// No shadowing errors, no fuss.
	//UPROPERTY()
	class USkeletalMeshComponent* Mesh;
	UPROPERTY()
	class APlayerController* PlayerController;
	// Player HUD and Player HUD class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPlayerHUD* PlayerHUD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UPlayerHUD> HUDClass;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = "Dash")
	void Dash();
	UFUNCTION(BlueprintCallable, Category = "Levitate")
	void Levitate();
	UFUNCTION(BlueprintCallable, Category = "Levitate")
	void StopLevitate();
	UFUNCTION(BlueprintCallable, Category = "Dash")
	void StopDash();
	UFUNCTION(BlueprintCallable, Category = "Spellcasting")
	void CastInput();
	
	// These functions bind delegates the weapon and the animation have for each other.
	UFUNCTION()
	void BindWeaponAndAnimEvents();

	// These functions bind delegates the stat components and the player HUD have.
	UFUNCTION()
	void BindHUDAndStatComponentEvents();

	void Landed(const FHitResult& Hit) override;
	


	//UFUNCTION(BlueprintCallable, Category = "Dash")
	//void UpdateDashLocation(float alpha);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// THESE MUST STAY PUBLIC IN ORDER FOR THE DELEGATE BINDINGS TO CALL THEM.
	UFUNCTION()
	void BindToOnAnimComplete();
	UFUNCTION()
	void BindToOnSpawnSpell();
	UFUNCTION()
	void BindToOnCast(float _manaCost);
	UFUNCTION()
	void BindToOnSpellChange(UAnimSequenceBase* CastAsset, float ScrollDirection);
	UFUNCTION()
	void BindToOnDamaged(float _ratio);
	UFUNCTION()
	void BindToOnManaUsed(float _ratio);

	// These are inherited from Rizzard Avatar.
	virtual void AvatarDamaged(float _ratio) override;
	virtual void AvatarDeath(float _ratio) override;
};

