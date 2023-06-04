// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/EffectComponent.h"
#include "Components/HealthComponent.h"
#include "BaseBlockout.generated.h"

UCLASS()
class THERIZZARD_API ABaseBlockout : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBlockout();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Method to handle the spell cast with fire, which can be accessed and overridden in blueprint
	UFUNCTION(BlueprintNativeEvent, Category = "Spell")
	void OnInteractedWithSpell(ESpellEffects spellType);
	virtual void OnInteractedWithSpell_Implementation(ESpellEffects spellType);


protected:
	//Component to handle the effects
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UEffectComponent* EffectComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TEnumAsByte<ESpellEffects> SpellNeeded;

	//box collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* BoxCollision;
	

};
