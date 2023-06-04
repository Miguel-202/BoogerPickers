// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EarthFist.h"
#include "GameFramework/Character.h"

// Sets default values
AEarthFist::AEarthFist()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TimeToDestroy = 1800.f;
}

// Called when the game starts or when spawned
void AEarthFist::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEarthFist::HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult)
{
	ImpactRotation = (OtherActor->GetActorLocation() - GetActorLocation()).Rotation();

	Super::HandleOverlap(OtherActor, OtherComp, SweepResult);
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter)
	{
		// Calculate the knockback direction
		FVector KnockbackDirection = (OtherActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();

		// Apply the knockback
		OtherCharacter->LaunchCharacter(KnockbackDirection * KnockbackForce, true, true);
	}
}

// Called every frame
void AEarthFist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

