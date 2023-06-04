// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseSpell.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include <Kismet/GameplayStatics.h>
#include "Animation/AnimSequenceBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
ABaseSpell::ABaseSpell()
{
	/*Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName("OverlapAll");
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseSpell::HandleCollision);


	FVector Scale = FVector(.6f, .6f, .6f);
	Mesh->SetWorldScale3D(Scale);*/
	TimeToDestroy = 5.f;
	RadialDamage = false;
	ImpactRotation = FRotator();
	Damage = 1.f;

}

// Called when the game starts or when spawned
void ABaseSpell::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle unused;
	GetWorld()->GetTimerManager().SetTimer(unused, this, &ABaseSpell::Deactivate, TimeToDestroy, false);
}

void ABaseSpell::HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult)
{
	auto ImpactParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, GetActorLocation() + FVector(0, 0, 20), ImpactRotation, true, EPSCPoolMethod::None, true);

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
	if (!RadialDamage)
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), GetInstigator(), DamageType);
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Radial"))
		TArray<AActor*> ignore;
		UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), 50.f, DamageType, ignore, GetInstigator(), GetInstigatorController());
	}
}

void ABaseSpell::HandleCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//check if the other actor is valid and is not the instigator
	if (!OtherActor || OtherActor == this || OtherActor == GetInstigator())
	{
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
	
	HandleOverlap(OtherActor, OtherComp, SweepResult);
}

float ABaseSpell::GetManaCost() {
	return ManaCost;
}

UAnimSequenceBase* ABaseSpell::GetCastAsset() {
	return SpellCastAsset;
}