// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTypes/IceType.h"
#include "Components/EffectComponent.h"

UIceType::UIceType()
{
}

void UIceType::StartEffect(AActor* DamagedActor, AActor* DamageCauser) const
{
	UEffectComponent* EffectComponent = DamagedActor->FindComponentByClass<UEffectComponent>();
	if (EffectComponent)
	{
		EffectComponent->StartEffect(ESpellEffects::Ice, DamageCauser);
	}
}