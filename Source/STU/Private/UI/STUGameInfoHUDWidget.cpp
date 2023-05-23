// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGameInfoHUDWidget.h"
#include "STU_GameModeBase.h"
#include "STUPlayerState.h"

int32 USTUGameInfoHUDWidget::GetCurrentRoundTime() const
{
	const auto GameMode = GetCurrentWorld();

	return GameMode ? GameMode->GetCurrentTime() : 0;
}

int32 USTUGameInfoHUDWidget::GetCurrentRound() const
{
	const auto GameMode = GetCurrentWorld();

	return GameMode ? GameMode->GetCurrentRound() : 0;
}

int32 USTUGameInfoHUDWidget::GetCurrentKillsNum() const
{
	const auto PlayerState = GetPlayerState();

	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 USTUGameInfoHUDWidget::GetRoundsNum() const
{
	const auto GameMode = GetCurrentWorld();

	return GameMode ? GameMode->GetRoundsNum().RoundsNum : 0;
}

ASTU_GameModeBase* USTUGameInfoHUDWidget::GetCurrentWorld() const
{
	return GetWorld() ? Cast<ASTU_GameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTUPlayerState* USTUGameInfoHUDWidget::GetPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}