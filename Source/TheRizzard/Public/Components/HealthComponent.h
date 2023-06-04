// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamageDispatcher, float, _ratio);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THERIZZARD_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetHealth(float NewHealth);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void HandleDamageDel(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Damage")
	FDamageDispatcher OnDamaged;
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Damage")
	FDamageDispatcher OnDeath;
};
