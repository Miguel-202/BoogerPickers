// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseSpellCast.h"
#include "Actors/BaseSpell.h"
#include "GameFramework/Character.h"
#include "Animation/AnimSequenceBase.h"


// Sets default values
ABaseSpellCast::ABaseSpellCast()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Dead = false;

	ActiveSpellNdx = 0;
}

// Called when the game starts or when spawned
void ABaseSpellCast::BeginPlay()
{
	Super::BeginPlay();
	
	ParentPawn = Cast<APawn>(this->GetParentActor());
	CostToCast = SpellClass->GetDefaultObject<ABaseSpell>()->GetManaCost();
}

void ABaseSpellCast::AnimationComplete() {
	Animating = false;
}

bool ABaseSpellCast::CanCast(float ManaAvailable) {
	
	
	return !Animating && !Dead && CostToCast <= ManaAvailable;
}

void ABaseSpellCast::Corpse(){
	Dead = true;
}

void ABaseSpellCast::CastSpell(float ManaAvailable) {
	if (CanCast(ManaAvailable))
	{
		Animating = true;
		OnCast.Broadcast(CostToCast);
		SpawnLocation = nullptr;
		AimRotation = nullptr;
	}
}

void ABaseSpellCast::SpawnSpell() {
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = ParentPawn->GetController();
	SpawnParams.Instigator = ParentPawn;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
	SpawnLocation = new FVector(Cast<ACharacter>(GetParentActor())->GetMesh()->GetSocketLocation(FName(TEXT("LeftHandCast"))));
	AimRotation = new FRotator(ParentPawn->GetBaseAimRotation());
	GetWorld()->SpawnActor(SpellClass, SpawnLocation, AimRotation, SpawnParams);
}

void ABaseSpellCast::ChangeActiveSpell(int DeltaNdx) {
	
	if (SpellClasses.IsValidIndex(ActiveSpellNdx - DeltaNdx) && !Animating) //DeltaNdx when scrolling up is positive, and negative when scrolled down.
	{
		ActiveSpellNdx -= DeltaNdx;
		SpellClass = SpellClasses[ActiveSpellNdx];
		CostToCast = SpellClass->GetDefaultObject<ABaseSpell>()->GetManaCost();
		OnSpellChange.Broadcast(SpellClass->GetDefaultObject<ABaseSpell>()->GetCastAsset(), DeltaNdx);
	}
}