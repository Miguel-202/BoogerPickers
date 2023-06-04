// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "RangedAIController.generated.h"

/**
 * 
 */
UCLASS()
class THERIZZARD_API ARangedAIController : public AAIController
{
	GENERATED_BODY()

public:

	ARangedAIController();


protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBehaviorTree* BTAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName PlayerName;
	UPROPERTY(BlueprintReadOnly)
		UAIPerceptionComponent* AIPerception;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float FleeRange;

	// helper function for Perception logic. THIS WILL MOST DEFINITELY BE TEMPORARY. -Sean J.
	UFUNCTION()
	bool IsTooClose(FVector _AILocation, FVector _PlayerLocation);

	UFUNCTION()
	void PerceptionUpdate(AActor* _Actor, FAIStimulus _Stimulus);

};
