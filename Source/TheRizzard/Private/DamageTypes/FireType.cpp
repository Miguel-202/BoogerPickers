// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTypes/FireType.h"
#include "Components/EffectComponent.h"


UFireType::UFireType()
{
}

void UFireType::StartEffect(AActor* DamagedActor, AActor* DamageCauser) const
{
	UEffectComponent* EffectComponent = DamagedActor->FindComponentByClass<UEffectComponent>();
	if (EffectComponent)
	{
		EffectComponent->StartEffect(ESpellEffects::Fire, DamageCauser);
	}
}