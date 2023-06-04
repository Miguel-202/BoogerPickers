// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RangedEnemy.h"
#include "Components/ChildActorComponent.h"
#include "Actors/BaseSpellCast.h"
#include "AnimationInstance/RizzardAnim.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "BrainComponent.h"

ARangedEnemy::ARangedEnemy() {
	
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	Mesh = GetMesh();
	CastComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("CastComponent"));
	CastComponent->SetupAttachment(Mesh);
	CastComponent->AttachToComponent(CastComponent->GetAttachParent(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("LeftHandCast")));
}

void ARangedEnemy::BeginPlay() {
	
	Super::BeginPlay();

	// Setting the CastComponent actor Class
	CastComponent->SetChildActorClass(SpellCastClass);
	// Getting the CastComponent object reference
	CastFocus = Cast<ABaseSpellCast>(CastComponent->GetChildActor());
	AnimBP = Cast<URizzardAnim>(Mesh->GetAnimInstance());
	BindWeaponAndAnimEvents();
}

void ARangedEnemy::CastInput() {
	CastFocus->CastSpell(10000.f);
}

void ARangedEnemy::BindWeaponAndAnimEvents() {
	AnimBP->OnAnimComplete.AddDynamic(this, &ARangedEnemy::BindToOnAnimComplete);
	AnimBP->OnSpawnSpell.AddDynamic(this, &ARangedEnemy::BindToOnSpawnSpell);
	CastFocus->OnCast.AddDynamic(this, &ARangedEnemy::BindToOnCast);
}

void ARangedEnemy::BindToOnAnimComplete() {
	CastFocus->AnimationComplete();
	FAIMessage::Send(this, FAIMessage(TEXT("AnimFinished"), nullptr, true)); // This sends a message to BTTask_Shoot that the task is no longer in progress, and is complete. -Sean J.
}

void ARangedEnemy::BindToOnSpawnSpell() {
	CastFocus->SpawnSpell();
}

void ARangedEnemy::BindToOnCast(float _dscrd) {
	AnimBP->PlayCastAnimation();
}

void ARangedEnemy::AvatarDamaged(float _ratio) {
	AnimBP->PlayHurtAnimation();
}

void ARangedEnemy::AvatarDeath(float _ratio) {
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->StopMovementImmediately();
	Movement->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CastFocus->Corpse();
	Mesh->SetCollisionProfileName(FName(TEXT("Ragdoll")));
	Mesh->SetSimulatePhysics(true);
}