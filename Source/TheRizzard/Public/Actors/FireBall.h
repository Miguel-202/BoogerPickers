// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseProjectile.h"
#include "FireBall.generated.h"

/**
 * 
 */
UCLASS()
class THERIZZARD_API AFireBall : public ABaseProjectile
{
	GENERATED_BODY()
public:
	AFireBall();
private:
	void HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult) override;
};
