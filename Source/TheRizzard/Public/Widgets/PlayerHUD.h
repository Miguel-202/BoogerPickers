// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class THERIZZARD_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UPlayerHUD(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* HealthBar;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* BossHealthBar;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* ManaBar;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* EquippedSpell;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* BSpell;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* USpell;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* BoSpell;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UImage*> SpellIcons;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* Crosshair;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UScrollBox* SpellScroll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor EquippedColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor DefaultColor;

	float SpellIconSize;
	float CurrentOffset;
	int SpellIconNdx;


public:
	UFUNCTION(BlueprintCallable)
	void SetHealth(float ratio);
	UFUNCTION(BlueprintCallable)
	void SetMana(float ratio);
	UFUNCTION()
	void SetOffset(float ScrollDirection);
	void SetIconColors(int DeltaNdx);
};
