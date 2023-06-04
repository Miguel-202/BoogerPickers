// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TheRizzrdAvatar.h"
#include "Interfaces/CastInterface.h"
#include "RangedEnemy.generated.h"

/**
 * 
 */
UCLASS()
class THERIZZARD_API ARangedEnemy : public ATheRizzrdAvatar, public ICastInterface
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* CastComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABaseSpellCast> SpellCastClass;

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABaseSpellCast* CastFocus;
	class USkeletalMeshComponent* Mesh;

	UFUNCTION(BlueprintCallable, Category = "Spellcasting")
	virtual void CastInput() override;

	// Invisible function to isolate all the delegate binds somewhere else
	UFUNCTION()
	void BindWeaponAndAnimEvents();

public:

	ARangedEnemy();

	UFUNCTION()
	void BindToOnAnimComplete();
	UFUNCTION()
	void BindToOnSpawnSpell();
	UFUNCTION()
	void BindToOnCast(float _dscrd);

	// These are inherited from Rizzard Avatar. // Might turn this into a interface sometime later.
	virtual void AvatarDamaged(float _ratio) override;
	virtual void AvatarDeath(float _ratio) override;
};
