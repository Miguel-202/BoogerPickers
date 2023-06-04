// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ManaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FManaDispatcher, float, _ratio);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THERIZZARD_API UManaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UManaComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mana")
	float Mana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana")
	float MaxMana;
	UFUNCTION(BlueprintCallable, Category = "Function")
	void RegenMana(float ManaRegen);
	void TurnOnRegen();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana")
	float RegenBufferTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana")
	float ManaRegenPerSecond;
	bool ShouldRegen;
	FTimerHandle RegenTimerHandle;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Function")
	void SetMana(float NewMana);
	UFUNCTION(BlueprintCallable, Category = "Function")
	float GetMana();
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Mana")
	FManaDispatcher OnManaUsed;
};
