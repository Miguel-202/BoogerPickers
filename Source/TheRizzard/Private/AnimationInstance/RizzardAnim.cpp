// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationInstance/RizzardAnim.h"
#include "Animation/AnimSequenceBase.h"

void URizzardAnim::PersonaUpdate()
{
	if (DebugCast)
	{
		PlayCastAnimation();
	}
}

void URizzardAnim::PlayCastAnimation() {
	PlaySlotAnimationAsDynamicMontage(CastAsset, FName(TEXT("Action")));
}

void URizzardAnim::PlayHurtAnimation() {
	PlaySlotAnimationAsDynamicMontage(HurtAsset, FName(TEXT("Damage")));
}

void URizzardAnim::SetCastAsset(UAnimSequenceBase* _NewCastAsset) {
	CastAsset = _NewCastAsset;
}