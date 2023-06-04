// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "Interfaces/EffectInterface.h"
#include "FireType.generated.h"

UCLASS()
class THERIZZARD_API UFireType : public UDamageType, public IEffectInterface
{
	GENERATED_BODY()

public:
	UFireType();
	
	virtual void StartEffect(AActor* DamagedActor, AActor* DamageCauser) const override;
};
