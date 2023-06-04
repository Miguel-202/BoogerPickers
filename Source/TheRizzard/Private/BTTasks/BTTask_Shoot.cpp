// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTTask_Shoot.h"
#include "AIController.h"
#include "Interfaces/CastInterface.h"

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory) {
	APawn* temp = _OwnerComp.GetAIOwner()->GetPawn();
	if (temp->GetClass()->ImplementsInterface(UCastInterface::StaticClass()))
	{
		
		Cast<ICastInterface>(temp)->CastInput();
		_OwnerComp.RegisterMessageObserver(this, TEXT("AnimFinished")); // Check Ranged Enemy's BindToOnAnimComplete for details. -Sean J.
	}
	return EBTNodeResult::InProgress;
}