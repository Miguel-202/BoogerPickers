// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTypes/FireType.h"
#include "EarthType.generated.h"

/**
 * 
 */
UCLASS()
class THERIZZARD_API UEarthType : public UFireType
{
	GENERATED_BODY()
	
protected:
	void StartEffect(AActor* DamagedActor, AActor* DamageCauser) const override;
};
