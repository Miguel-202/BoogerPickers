// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DistanceCheck.generated.h"

/**
 * 
 */
UCLASS()
class THERIZZARD_API UBTTask_DistanceCheck : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& _Task) {}

};
