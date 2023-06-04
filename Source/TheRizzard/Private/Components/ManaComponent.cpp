// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ManaComponent.h"

// Sets default values for this component's properties
UManaComponent::UManaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	RegenBufferTime = 1.f;
	ShouldRegen = false;
	// ...
}


// Called when the game starts
void UManaComponent::BeginPlay()
{
	Super::BeginPlay();

	Mana = MaxMana;
	// ...

}


// Called every frame
void UManaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldRegen)
		RegenMana(DeltaTime * ManaRegenPerSecond);
	// ...
}

void UManaComponent::SetMana(float NewMana)
{
	Mana = FMath::Clamp(Mana - NewMana, 0, MaxMana);
	OnManaUsed.Broadcast(Mana / MaxMana);
	ShouldRegen = false;
	GetWorld()->GetTimerManager().ClearTimer(RegenTimerHandle); // this SHOULD clear the timer set before. Unreal docs said it wasn't thread safe though sooooo... ¯\_:)_/¯ -Sean J.
	GetWorld()->GetTimerManager().SetTimer(RegenTimerHandle, this, &UManaComponent::TurnOnRegen, RegenBufferTime);
}

// I decided to split mana use and regen for ease of reading and understanding code in the future. -Sean J.
void UManaComponent::RegenMana(float ManaRegen) 
{
	Mana = FMath::Clamp(Mana + ManaRegen, 0, MaxMana);
	OnManaUsed.Broadcast(Mana / MaxMana);
	if (Mana == MaxMana)
	{
		ShouldRegen = false;
	}
}

float UManaComponent::GetMana()
{
	return Mana;
}

// The reason for this function's existence? As far as I know, timermanager only calls a function once after time's up.
void UManaComponent::TurnOnRegen() 
{
	ShouldRegen = true;
}

