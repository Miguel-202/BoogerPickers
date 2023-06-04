// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTypes/EarthType.h"
#include "Components/EffectComponent.h"

void UEarthType::StartEffect(AActor* DamagedActor, AActor* DamageCauser) const
{
	UEffectComponent* EffectComponent = DamagedActor->FindComponentByClass<UEffectComponent>();
	if (EffectComponent)
	{
		EffectComponent->StartEffect(ESpellEffects::Earth, DamageCauser);
	}
}
