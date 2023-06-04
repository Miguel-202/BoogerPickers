// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/RangedAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

ARangedAIController::ARangedAIController() : Super() {
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 1500.f;
	SightConfig->PeripheralVisionAngleDegrees = 35.f;
	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ARangedAIController::PerceptionUpdate);
}

void ARangedAIController::OnPossess(APawn* InPawn) {

	Super::OnPossess(InPawn);
	RunBehaviorTree(BTAsset);
}

void ARangedAIController::BeginPlay() {
	Super::BeginPlay();
	Blackboard->SetValueAsFloat(FName(TEXT("FleeRange")), FleeRange);
}

bool ARangedAIController::IsTooClose(FVector _AILocation, FVector _PlayerLocation)
{
	return (_PlayerLocation - _AILocation).Length() < FleeRange;
}

void ARangedAIController::PerceptionUpdate(AActor* _Actor, FAIStimulus _Stimulus) { // This is naive, I'll have to create my own Dev Settings, Game Mode, Enum and structs to make this optimal. Enough work to be it's own Epic. -Sean J.
	
	bool temp = _Actor->ActorHasTag(PlayerName);
	bool sensed = _Stimulus.WasSuccessfullySensed();
	if (temp)
	{
		if (sensed)
		{
			bool tooClose = IsTooClose(GetPawn()->GetActorLocation(), _Actor->GetActorLocation());
			if (tooClose)
			{
				Blackboard->SetValueAsBool(FName(TEXT("Fleeing")), true);
			}
			else
				Blackboard->ClearValue(FName(TEXT("Fleeing")));
			Blackboard->SetValueAsObject(PlayerName, _Actor);
		}
		else if (!sensed && Blackboard->GetBlackboardAsset()->GetKey(Blackboard->GetKeyID(FName(TEXT("Fleeing"))))->KeyType->WrappedIsEmpty(*Blackboard, Blackboard->GetKeyRawData(FName(TEXT("Fleeing"))))) // I swear on my LIFE that I will optimize this later. -Sean J. Update: This is some NEXT LEVEL BULLSHIT. -Sean J.
		{ 
			// This horrendous if check sees if the blackboard variable is set. -Sean J.
			// Update: Why. Why did this work. Why did it need to? Couldn't it just not have worked so I could erase this horrible, GODFORSAKEN code? -Sean J.
			Blackboard->ClearValue(PlayerName);
		}	
	}
}