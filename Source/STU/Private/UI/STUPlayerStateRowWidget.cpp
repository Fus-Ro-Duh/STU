// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUPlayerStateRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTUPlayerStateRowWidget::SetPlayerName(const FText& Text)
{
	if (!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void USTUPlayerStateRowWidget::SetKills(const FText& Text)
{
	if (!PlayerKillsTextBlock) return;
	PlayerKillsTextBlock->SetText(Text);
}

void USTUPlayerStateRowWidget::SetDeaths(const FText& Text)
{
	if (!PlayerDeathsTextBlock) return;
	PlayerDeathsTextBlock->SetText(Text);
}

void USTUPlayerStateRowWidget::SetTeam(const FText& Text)
{
	if (!PlayerTeamTextBlock) return;
	PlayerTeamTextBlock->SetText(Text);
}

void USTUPlayerStateRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if (!PlayerIndicatorWidget) return;
	PlayerIndicatorWidget->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTUPlayerStateRowWidget::SetTeamColor(const FLinearColor& Color)
{
	if (!TeamImage) return;
	TeamImage->SetColorAndOpacity(Color);
}
