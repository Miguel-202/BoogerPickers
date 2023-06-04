// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTTask_FindPoint.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_FindPoint::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory) {

	Radius = 1000.f;
	FVector temp = FVector::ZeroVector;
	FNavLocation ResultLocation;
	if (FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld())->K2_GetRandomLocationInNavigableRadius(GetWorld(), _OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), temp, Radius))
		_OwnerComp.GetBlackboardComponent()->SetValueAsVector(OutputVector.SelectedKeyName, temp);
	else
		return EBTNodeResult::Failed;
	
	return EBTNodeResult::Succeeded;
}
