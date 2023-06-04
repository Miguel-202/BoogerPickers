// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTTask_DistanceCheck.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_DistanceCheck::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory) {
	UBlackboardComponent* temp = _OwnerComp.GetBlackboardComponent();
	APawn* AIPawn = _OwnerComp.GetAIOwner()->GetPawn();
	FVector distanceVector = (Cast<AActor>(temp->GetValueAsObject(FName(TEXT("Player"))))->GetActorLocation() - AIPawn->GetActorLocation());
	if (distanceVector.Length() < temp->GetValueAsFloat(FName(TEXT("FleeRange")))) // compares distance from player to AI actor. -Sean J.
	{
		temp->SetValueAsBool(FName(TEXT("Fleeing")), true);
		temp->SetValueAsVector(FName(TEXT("Destination")), distanceVector.GetUnsafeNormal() * 700);
	}
	else
		temp->ClearValue(FName(TEXT("Fleeing")));
	return EBTNodeResult::Succeeded;
}