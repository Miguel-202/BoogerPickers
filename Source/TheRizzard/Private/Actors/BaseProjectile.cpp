// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{

	   //BELOW STUFF IS IMPLEMENTED IN BLUEPRINT
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetCollisionProfileName("Custom");
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::HandleCollision);
	
	FlyingParticles = CreateDefaultSubobject<UParticleSystemComponent>("Flying Particles");
	FlyingParticles->SetupAttachment(Collision);

	FlyingParticles->SetTemplate(MovingParticle);
	/*Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionProfileName("NoCollision");
	Mesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	Mesh->SetGenerateOverlapEvents(false);
	

	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>("Particle System");
	ParticleSystem->SetupAttachment(Mesh);


	Mesh->SetWorldScale3D(Scale);
	*/
	FVector Scale = FVector(.6f, .6f, .6f);

	Collision->SetWorldScale3D(Scale);
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	GetDestroyed = true;
	Movement->InitialSpeed = 1800;
	Movement->MaxSpeed = 2000;
	Movement->ProjectileGravityScale = 0.f;
	TimeToDestroy = 3.f;
	Damage = 1.f;

}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
}

void ABaseProjectile::HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, FHitResult SweepResult)
{
	Super::HandleOverlap(OtherActor, OtherComp, SweepResult);
	if (!IsPendingKill() && GetDestroyed)
	{
		Destroy();
	}
}

void ABaseProjectile::TimerEnded()
{
	Destroy();
}

