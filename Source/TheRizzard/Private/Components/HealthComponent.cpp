// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Interfaces/EffectInterface.h"
//#include "DamageTypes/FireType.h"
//#include "Components/EffectComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100;
	Health = MaxHealth;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamageDel);
	
}

void UHealthComponent::SetHealth(float NewHealth)
{
	Health = NewHealth;
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::HandleDamageDel(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	// Health will be between 0 or Max
	Health = FMath::Clamp(Health - Damage, 0, MaxHealth);
	// this will apply whatever effect it's hit by
	auto effect = Cast<IEffectInterface>(DamageType);
	if (effect)
	{
		effect->StartEffect(DamagedActor, DamageCauser);
	}
	//log to screen HIT DEBUG ONLY
	UE_LOG(LogTemp, Warning, TEXT("HIT"));
	if (Health > 0)
	{
		//TODO: Broadcast health ratio

		if (Damage > 0)
		{
			//Broadcast Damage
			OnDamaged.Broadcast(Health / MaxHealth);
		}
		else
		{
			//Broadcast Heal
		}
		
	}
	else
	{
		// Actor Can't take damage anymore
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::HandleDamageDel);
		//TODO: Broadcast health ratio, and character death
		OnDeath.Broadcast(Health / MaxHealth);
	}

}

