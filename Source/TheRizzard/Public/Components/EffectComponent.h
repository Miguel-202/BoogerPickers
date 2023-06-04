// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EffectComponent.generated.h"

UENUM(BlueprintType) 
enum ESpellEffects 
{
	Fire UMETA(DisplayName = "Fire"),
	Ice UMETA(DisplayName = "Ice"),
	Air UMETA(DisplayName = "Air"),
	Earth UMETA(DisplayName = "Earth"),
	NumEffects 
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THERIZZARD_API UEffectComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireIceComboDelegate);
	// Sets default values for this component's properties
	UEffectComponent();

	//Delegates
	FOnFireIceComboDelegate OnFireIceCombo;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	float SecondsToCombo;
	bool hasFireEffect;
	bool hasIceEffect;
	bool hasAirEffect;
	bool hasEarthEffect;

	void ResetFireEffect();
	void ResetIceEffect();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void StartEffect(ESpellEffects Type, AActor* DamageCauser);

	//FireEffectClass
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TSubclassOf<class AFireEffect> FireEffectClass;
	//IceEffectClass
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TSubclassOf<class AIceEffect> IceEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TSubclassOf<class AIceEffect> EarthEffectClass;

	//blueprint editable function to manage FireIceCombo BlueprintNativeEvent
	UFUNCTION(BlueprintCallable, Category = "Effect")
	void FireIceCombo();


		
};
