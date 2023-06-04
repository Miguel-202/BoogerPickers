// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FrostBite.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"


AFrostBite::AFrostBite()
{
	InitialLifeSpan = 3.f;
}

void AFrostBite::HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult)
{
	//check if the other actor is valid and is not the instigator
	if (!OtherActor || OtherActor == this || OtherActor == GetInstigator())
	{
		return;
	}
	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), GetInstigator(), DamageType);
	// Only Destroy once it hits an object
	if (!Cast<ACharacter>(OtherActor))
	{
		Destroy();
	}
}
