// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/IceEffect.h"
#include "TheRizzard/TheRizzrdAvatar.h"
#include "GameFramework/CharacterMovementComponent.h"

//constructor
AIceEffect::AIceEffect()
{
	DamagePerSecond = 1.f;
	InitialLifeSpan = 3;
    SlowFactor = 5.f;
}

//begin play
void AIceEffect::BeginPlay()
{
	Super::BeginPlay();
    // Add a delay of 0.1 seconds before running any code
    const float DelayDuration = 0.1f;
    FTimerHandle TimerHandle;
    FTimerDelegate TimerDelegate;
    TimerDelegate.BindLambda([this, DelayDuration]() {
        ATheRizzrdAvatar* Avatar = Cast<ATheRizzrdAvatar>(GetAttachParentActor());
        if (Avatar)
        {
            float OriginalMaxWalkSpeed = Avatar->GetCharacterMovement()->MaxWalkSpeed;
            Avatar->GetCharacterMovement()->MaxWalkSpeed /= SlowFactor;

            // Set character max walk speed back to normal after 3 seconds
            FTimerHandle Timer;
            FTimerDelegate ResetSpeedDelegate;
            ResetSpeedDelegate.BindLambda([Avatar, OriginalMaxWalkSpeed]() {
                Avatar->GetCharacterMovement()->MaxWalkSpeed = OriginalMaxWalkSpeed;
                });
            GetWorldTimerManager().SetTimer(Timer, ResetSpeedDelegate, InitialLifeSpan - DelayDuration, false);
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Avatar not found"));
            if (GetAttachParentActor() != nullptr)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, GetAttachParentActor()->GetClass()->GetName());
            }
		});
    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, DelayDuration, false);




	//ATheRizzrdAvatar* avatar = Cast<ATheRizzrdAvatar>(GetAttachParentActor());
 //   if (avatar)
 //   {
 //       float originalMaxWalkSpeed = avatar->GetCharacterMovement()->MaxWalkSpeed;
 //       avatar->GetCharacterMovement()->MaxWalkSpeed /= 5;

 //       // Set character max walk speed back to normal after 3 seconds
 //       FTimerHandle timer;
 //       GetWorldTimerManager().SetTimer(timer, [avatar, originalMaxWalkSpeed]() {
 //           avatar->GetCharacterMovement()->MaxWalkSpeed = originalMaxWalkSpeed;
 //           }, InitialLifeSpan - 0.1f, false);

 //       GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Avatar found"));
 //   }
 //   else
 //   {
 //       GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Avatar not found"));
 //       if (GetAttachParentActor() != nullptr)
 //           GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, GetAttachParentActor()->GetClass()->GetName());
 //   }
}

//tick
void AIceEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}