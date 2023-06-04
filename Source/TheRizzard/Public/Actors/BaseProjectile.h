// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseSpell.h"
#include "BaseProjectile.generated.h"

UCLASS(abstract)
class THERIZZARD_API ABaseProjectile : public ABaseSpell
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult) override;
	UFUNCTION()
	void TimerEnded();
	// //BELOW STUFF IS IMPLEMENTED IN BLUEPRINT
	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	class USphereComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	class UProjectileMovementComponent* Movement;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	class UParticleSystemComponent* FlyingParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* MovingParticle;
	//UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	//class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	class UNiagaraComponent* ParticleSystem;

	bool GetDestroyed;

};
