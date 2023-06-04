// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageTypes/FireType.h"
#include "IceType.generated.h"

/**
 * 
 */
UCLASS()
class THERIZZARD_API UIceType : public UFireType
{
	GENERATED_BODY()
public:
	UIceType();
	void StartEffect(AActor* DamagedActor, AActor* DamageCauser) const override;

};
