// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "BaseSpellCast.generated.h"

// There will be a AnimSequence pointer variable added to this later.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCast, float, _manaCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpellChange, UAnimSequenceBase*, _castAnim, float, _scrollDirection);

UCLASS()
class THERIZZARD_API ABaseSpellCast : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSpellCast();

	FVector* SpawnLocation;
	FRotator* AimRotation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	APawn* ParentPawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<class ABaseSpell>> SpellClasses;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<class ABaseSpell> SpellClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool Animating;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool Dead;
	UPROPERTY()
	float CostToCast;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int ActiveSpellNdx;

public:

	UFUNCTION()
	void AnimationComplete();
	UFUNCTION()
	bool CanCast(float ManaAvailable);
	// Turns the 'Dead' boolean on, so you can't shoot while you're dead.
	UFUNCTION()
	void Corpse();
	UFUNCTION()
	void CastSpell(float ManaAvailable);
	UFUNCTION()
	void SpawnSpell();
	UFUNCTION()
	void ChangeActiveSpell(int DeltaNdx);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FOnCast OnCast;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FOnSpellChange OnSpellChange;
};
