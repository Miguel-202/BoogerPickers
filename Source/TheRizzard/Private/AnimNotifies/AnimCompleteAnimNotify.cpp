// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AnimCompleteAnimNotify.h"
#include "AnimationInstance/RizzardAnim.h"

void UAnimCompleteAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (MeshComp != NULL && MeshComp->GetAnimInstance() != NULL)
	{
		URizzardAnim* AnimBP = Cast<URizzardAnim>(MeshComp->GetAnimInstance());
		if (AnimBP != NULL)
			AnimBP->OnAnimComplete.Broadcast();
	}
}