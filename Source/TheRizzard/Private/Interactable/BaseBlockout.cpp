// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/BaseBlockout.h"
#include "Components/EffectComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseBlockout::ABaseBlockout()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set box collision as root component and to enable overlap events and have collisison
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//set box collision as root component
	SetRootComponent(BoxCollision);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	EffectComponent = CreateDefaultSubobject<UEffectComponent>(TEXT("EffectComponent"));


}

// Called when the game starts or when spawned
void ABaseBlockout::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseBlockout::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBlockout::OnInteractedWithSpell_Implementation(ESpellEffects spellType)
{
}


