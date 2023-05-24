// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStateRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class STU_API USTUPlayerStateRowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetPlayerName(const FText& Text);
	void SetKills(const FText& Text);
	void SetDeaths(const FText& Text);
	void SetTeam(const FText& Text);
	void SetPlayerIndicatorVisibility(bool Visible);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerKillsTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerDeathsTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerTeamTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* PlayerIndicatorWidget;
};
