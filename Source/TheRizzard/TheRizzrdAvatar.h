// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TheRizzrdAvatar.generated.h"

UCLASS(Abstract)
class THERIZZARD_API ATheRizzrdAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATheRizzrdAvatar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Animation Blueprint reference.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class URizzardAnim* AnimBP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UHealthComponent* HealthComponent;
	//effect component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UEffectComponent* EffectComponent;
		 
public:	
	
	// Since the AnimBP might be different for each and every avatar (Or not even use an Animation blueprint at all), I'll leave this one empty for child classes to fill in the blanks.
	UFUNCTION(CallInEditor, BlueprintCallable)
	virtual void AvatarDamaged(float _ratio) {};

	UFUNCTION(CallInEditor, BlueprintCallable)
	virtual void AvatarDeath(float _ratio) {};

	//BlueprintNativeEvent To handle Combo from Ice and Fire
	UFUNCTION(BlueprintNativeEvent, Category = "Spell")
	void OnFireIceCombo();
	virtual void OnFireIceCombo_Implementation();
};
