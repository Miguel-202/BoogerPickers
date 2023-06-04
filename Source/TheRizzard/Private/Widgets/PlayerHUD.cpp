// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"
//#include "Components/CanvasPanelSlot.h"


UPlayerHUD::UPlayerHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CurrentOffset = 0.f;
}

void UPlayerHUD::NativeConstruct() {
	SpellIconSize = EquippedSpell->Brush.GetImageSize().Y;
	SpellIconNdx = 0;
	SpellIcons.Add(EquippedSpell);
	SpellIcons.Add(BSpell);
	SpellIcons.Add(USpell);
	SpellIcons.Add(BoSpell);
	SetOffset(0.f);
}

void UPlayerHUD::SetHealth(float ratio)
{
	HealthBar->SetPercent(ratio);
}

void UPlayerHUD::SetMana(float ratio)
{
	ManaBar->SetPercent(ratio);
}

void UPlayerHUD::SetOffset(float ScrollDirection)
{
	// have to invert the scroll direction since downscrolling is shown as negative.
	CurrentOffset += -ScrollDirection * SpellIconSize;
	SpellScroll->SetScrollOffset(CurrentOffset);
	SetIconColors(ScrollDirection);
}

void UPlayerHUD::SetIconColors(int DeltaNdx) {
	SpellIcons[SpellIconNdx]->SetColorAndOpacity(DefaultColor);
	SpellIconNdx -= DeltaNdx;
	SpellIcons[SpellIconNdx]->SetColorAndOpacity(EquippedColor);
}