// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tornado.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystemComponent.h"


ATornado::ATornado()
{
	HasCollided = false;
	GetDestroyed = false;
	ActorCollided = 0;
}

void ATornado::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle ExpandCollisionTimerHandle;
	FTimerDelegate Expand;
	Expand.BindLambda([this]()
		{
			if (!HasCollided)
			{
				Collision->SetWorldScale3D(FVector(6, 6, 6));
				float ScaledRadius = Collision->GetUnscaledSphereRadius() * Collision->GetComponentScale().GetMax(
				
				);

				Collision->SetSphereRadius(ScaledRadius);
				Movement->Velocity = FVector::ZeroVector;

				
				HasCollided = true;
				// Spawn The Impact Particle Effect
				auto ImpactParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, GetActorLocation() + FVector(0, 0, 20), FRotator(), true, EPSCPoolMethod::None, true);
				FTimerHandle TimerHandle_DestroyParticle;
				// Destroy the particle component after a delay
				float DestroyDelay = 2.0f;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle_DestroyParticle, [ImpactParticleComponent]()
					{
						if (ImpactParticleComponent)
						{
							ImpactParticleComponent->Deactivate();
							ImpactParticleComponent->DestroyComponent();
						}
					}, DestroyDelay, false);
				
			}
		});
	// Set up a timer to expand the collision
	GetWorldTimerManager().SetTimer(ExpandCollisionTimerHandle, Expand, 1, false);
}

void ATornado::HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult)
{
	// Max number of actors
	ActorCollided++;
	if (ActorCollided >= CollisionLimit)
	{
		Destroy();
	}
	// Don't want to expand the collision more than once
	if (!HasCollided)
	{
		Collision->SetWorldScale3D(FVector(6, 6, 6));
		float ScaledRadius = Collision->GetUnscaledSphereRadius() * Collision->GetComponentScale().GetMax();

		Collision->SetSphereRadius(ScaledRadius);
		Movement->Velocity = FVector::ZeroVector;
	}
	HasCollided = true;
	// Get the character to launch
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	// Attract anybody that has overlapped
	if (OtherCharacter)
	{
		// Calculate the Attract direction towards the center of the tornado
		FVector AttractDirection = (GetActorLocation() - OtherCharacter->GetActorLocation());
		float DistanceToCenter = AttractDirection.Size(); // Get the distance to the center

		// Normalize the Attract direction
		AttractDirection.Normalize();

		// Calculate the force magnitude based on the distance to the center
		float ForceMagnitude = MaxForce * (1.0f - DistanceToCenter / Collision->GetScaledSphereRadius());

		// Apply the knockback force to the character
		OtherCharacter->LaunchCharacter(AttractDirection * ForceMagnitude, true, false);
	}
	Super::HandleOverlap(OtherActor, OtherComp, SweepResult);
}
