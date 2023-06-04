// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/FireEffect.h"
#include "TheRizzard/TheRizzrdAvatar.h"
#include "IceEffect.generated.h"

/**
 * 
 */
UCLASS()
class THERIZZARD_API AIceEffect : public AFireEffect
{
	GENERATED_BODY()
	
public:
	AIceEffect();

protected:
	//Editable from the blueprint value for slowness applied to the enemy as the dividend of the speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlowFactor;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
};
