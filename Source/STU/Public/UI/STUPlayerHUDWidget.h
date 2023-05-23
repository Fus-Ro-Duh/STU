// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

class UWeaponComponent;
class UHealthComponent;

UCLASS()
class STU_API USTUPlayerHUDWidget : public UUserWidget
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

	virtual bool Initialize() override;

private:
	void OnHealthChanged(float Health, float HealthDelta);
	void OnNewPawn(APawn* NewPawn);
};
