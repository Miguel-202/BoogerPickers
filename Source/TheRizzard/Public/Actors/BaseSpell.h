// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpell.generated.h"

UCLASS(abstract)
class THERIZZARD_API ABaseSpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSpell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Activate() {};
	UFUNCTION()
	virtual void Deactivate() { Destroy(); };
	virtual void HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult);
	UFUNCTION(BlueprintCallable)
	virtual void HandleCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ManaCost;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimeToDestroy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* SpellCastAsset;
	UPROPERTY(EditDefaultsOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	class USoundCue* Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* ImpactParticle;
	FRotator ImpactRotation;

	bool RadialDamage;

public:
	UFUNCTION(BlueprintCallable)
	float GetManaCost();
	UFUNCTION(BlueprintCallable)
	UAnimSequenceBase* GetCastAsset();
};
