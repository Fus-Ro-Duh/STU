// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

class UProgressBar;
class UWidgetAnim;

UCLASS()
class STU_API USTUPlayerHUDWidget : public USTUBaseWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Blueprintcallable, Category = "UI")
	float GetHealthPercent() const;

	UFUNCTION(Blueprintcallable, Category = "UI")
	bool GetWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(Blueprintcallable, Category = "UI")
	bool GetAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(Blueprintcallable, Category = "UI")
	bool IsPlayerAlive() const;

	UFUNCTION(Blueprintcallable, Category = "UI")
	bool IsPlayerSpectatic() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	UFUNCTION(Blueprintcallable, Category = "UI")
	FString FormatBullets(int32 BulletsNum) const;

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* DamageAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float PrecentColorThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor GoodColor = FLinearColor::Green;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor BadColor = FLinearColor::Red;

	virtual void NativeOnInitialized() override;

private:
	void OnHealthChanged(float Health, float HealthDelta);
	void OnNewPawn(APawn* NewPawn);
	void UpdateHealthBar();
};
