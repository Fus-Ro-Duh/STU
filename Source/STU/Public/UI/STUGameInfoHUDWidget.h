// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGameInfoHUDWidget.generated.h"

class ASTU_GameModeBase;
class ASTUPlayerState;

UCLASS()
class STU_API USTUGameInfoHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(Blueprintcallable, Category = "UI")
	int32 GetCurrentRoundTime() const;

	UFUNCTION(Blueprintcallable, Category = "UI")
	int32 GetCurrentRound() const;

	UFUNCTION(Blueprintcallable, Category = "UI")
	int32 GetCurrentKillsNum() const;

	UFUNCTION(Blueprintcallable, Category = "UI")
	int32 GetRoundsNum() const;

	ASTU_GameModeBase* GetCurrentWorld() const;
	ASTUPlayerState* GetPlayerState() const;

};
