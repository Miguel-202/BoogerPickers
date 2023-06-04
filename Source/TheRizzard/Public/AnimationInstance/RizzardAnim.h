// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RizzardAnim.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnSpell);

/**
 * 
 */
UCLASS()
class THERIZZARD_API URizzardAnim : public UAnimInstance
{
	GENERATED_BODY()

protected:

	// Debugging function for animation blueprint.
	UFUNCTION(BlueprintCallable)
	void PersonaUpdate();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool DebugCast;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequenceBase* CastAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequenceBase* HurtAsset;

public:

	UFUNCTION()
	void PlayCastAnimation();
	UFUNCTION()
	void PlayHurtAnimation();
	UFUNCTION()
	void SetCastAsset(UAnimSequenceBase* _NewCastAsset);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
	FOnAnimComplete OnAnimComplete;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
	FOnSpawnSpell OnSpawnSpell;
};
