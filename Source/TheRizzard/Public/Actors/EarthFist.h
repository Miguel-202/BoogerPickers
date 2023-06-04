// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/BaseSpell.h"
#include "EarthFist.generated.h"

UCLASS()
class THERIZZARD_API AEarthFist : public ABaseSpell
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEarthFist();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void Activate() override;
	void HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockbackForce;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
