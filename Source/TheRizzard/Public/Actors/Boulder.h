// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseProjectile.h"
#include "Boulder.generated.h"

/**
 * 
 */
UCLASS()
class THERIZZARD_API ABoulder : public ABaseProjectile
{
	GENERATED_BODY()
public:
	ABoulder();
private:
	void HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult) override;

};
