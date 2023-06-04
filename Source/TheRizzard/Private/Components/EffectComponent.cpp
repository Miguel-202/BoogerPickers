// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EffectComponent.h"
#include "Interactable/BaseBlockout.h"
#include "Actors/FireEffect.h"
#include "Actors/IceEffect.h"
#include "TheRizzard/TheRizzrdAvatar.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values for this component's properties
UEffectComponent::UEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SecondsToCombo = 3.0f;
	// ...
}


// Called when the game starts
void UEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEffectComponent::StartEffect(ESpellEffects Type, AActor* DamageCauser)
{
	switch (Type)
	{
	case ESpellEffects::Fire:
	{
		hasFireEffect = true;
		//set fire effect to false after SecondsToCombo
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UEffectComponent::ResetFireEffect, SecondsToCombo, false);
		FTransform Transform = GetOwner()->GetActorTransform();
		FActorSpawnParameters Params;
		Params.Owner = DamageCauser;
		auto temp = GetWorld()->SpawnActor<AFireEffect>(FireEffectClass, Transform, Params);
 		if (hasIceEffect)
		{
			FireIceCombo();
		}
		AActor* player = GetOwner();
		if (temp != nullptr)
			temp->AttachToActor(player, FAttachmentTransformRules::KeepWorldTransform);
		else
			UE_LOG(LogTemp, Warning, TEXT("FireEffectClass is null"));
	}
	break;
	case ESpellEffects::Ice:
	{
		FTransform Transform = GetOwner()->GetActorTransform();
		FActorSpawnParameters Params;
		Params.Owner = DamageCauser;
		hasIceEffect = true;
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UEffectComponent::ResetIceEffect, SecondsToCombo, false);
		ATheRizzrdAvatar* PlayerCharacter = Cast<ATheRizzrdAvatar>(GetOwner());
		if (PlayerCharacter)
		{
			AIceEffect* IceEffect = GetWorld()->SpawnActor<AIceEffect>(IceEffectClass, Transform, Params);
			if (IceEffect)
			{
				IceEffect->AttachToActor(PlayerCharacter, FAttachmentTransformRules::KeepWorldTransform);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("IceEffectClass is null"));
			}
			if (hasFireEffect)
			{
				FireIceCombo();
			}
		}
	}
		break;
	case ESpellEffects::Air:
	{

	}
		break;
	case ESpellEffects::Earth:
	{
		FTransform Transform = GetOwner()->GetActorTransform();
		FActorSpawnParameters Params;
		Params.Owner = DamageCauser;

		ATheRizzrdAvatar* PlayerCharacter = Cast<ATheRizzrdAvatar>(GetOwner());
		if (PlayerCharacter)
		{
			AIceEffect* EarthEffectChildOfIce = GetWorld()->SpawnActor<AIceEffect>(EarthEffectClass, Transform, Params);
			if (EarthEffectChildOfIce)
			{
				EarthEffectChildOfIce->AttachToActor(PlayerCharacter, FAttachmentTransformRules::KeepWorldTransform);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("EarthEffectClass is null"));
			}
		}
	}
		break;
	default:
		break;
	}

	ABaseBlockout* Blockout = Cast<ABaseBlockout>(GetOwner());
	if (Blockout)
	{
		Blockout->OnInteractedWithSpell(Type);
	}
}

void UEffectComponent::ResetFireEffect()
{
	hasFireEffect = false;
}

void UEffectComponent::ResetIceEffect()
{
	hasIceEffect = false;
}

void UEffectComponent::FireIceCombo()
{
	OnFireIceCombo.Broadcast();
	hasFireEffect = false;
	hasIceEffect = false;
}