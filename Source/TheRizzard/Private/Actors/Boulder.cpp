// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Boulder.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"

ABoulder::ABoulder()
{
	Movement->ProjectileGravityScale = 1.8f;
	Movement->bRotationFollowsVelocity = true;
	GetDestroyed = false;
}

void ABoulder::HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult)
{
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);

	if (OtherCharacter)
	{
		// Calculate the Attract direction towards the center of the tornado
		FVector AttractDirection = (OtherCharacter->GetActorLocation() - GetActorLocation());

		// Apply the knockback force to the character
		OtherCharacter->LaunchCharacter(AttractDirection * 2.5f, true, false);
		Super::HandleOverlap(OtherActor, OtherComp, SweepResult);

	}
	else
	{
		Collision->SetWorldScale3D(FVector(6, 6, 6));
		float ScaledRadius = Collision->GetUnscaledSphereRadius() * Collision->GetComponentScale().GetMax();

		Collision->SetSphereRadius(ScaledRadius);
		Destroy();
	}
}
