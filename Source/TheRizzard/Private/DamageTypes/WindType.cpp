// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTypes/WindType.h"
#include <Components/EffectComponent.h>

void UWindType::StartEffect(AActor* DamagedActor, AActor* DamageCauser) const
{
	UEffectComponent* EffectComponent = DamagedActor->FindComponentByClass<UEffectComponent>();
	if (EffectComponent)
	{
		EffectComponent->StartEffect(ESpellEffects::Air, DamageCauser);
	}
}
