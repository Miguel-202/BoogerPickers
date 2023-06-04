// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseProjectile.h"
#include "Tornado.generated.h"

/**
 * 
 */
UCLASS()
class THERIZZARD_API ATornado : public ABaseProjectile
{
	GENERATED_BODY()
public:
	ATornado();
protected:
	bool HasCollided;
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxForce;
	int ActorCollided;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int CollisionLimit;
	void HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult) override;
};
