// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimCompleteAnimNotify.h"
#include "SpawnSpellAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class THERIZZARD_API USpawnSpellAnimNotify : public UAnimCompleteAnimNotify
{
	GENERATED_BODY()
	
private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
