// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseProjectile.h"
#include "FrostBite.generated.h"

/**
 * 
 */
UCLASS()
class THERIZZARD_API AFrostBite : public ABaseProjectile
{
	GENERATED_BODY()
public:
	AFrostBite();
private:
	void HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult) override;
};
