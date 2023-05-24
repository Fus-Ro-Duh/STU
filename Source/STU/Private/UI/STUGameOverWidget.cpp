// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGameOverWidget.h"
#include "STU_GameModeBase.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStateRowWidget.h"
#include "Components/VerticalBox.h"
#include "STU_Utils.h"

bool USTUGameOverWidget::Initialize()
{
	if (GetWorld())
	{
		const auto GameMode = Cast<ASTU_GameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
		}

	}

	return Super::Initialize();
}

void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState State)
{
	if (State == ESTUMatchState::GameOver)
	{
		UpdatePlayersState();
	}
}

void USTUGameOverWidget::UpdatePlayersState()
{
	if (!GetWorld() && !PlayerStateBox) return;

	PlayerStateBox->ClearChildren();

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		const auto PlayerStateRowWidget = CreateWidget<USTUPlayerStateRowWidget>(GetWorld(), PlayerStateRowWidgetClass);
		if (!PlayerStateRowWidget) continue;

		PlayerStateRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStateRowWidget->SetKills(STU_Utils::TextFromInt(PlayerState->GetKillsNum()));
		PlayerStateRowWidget->SetDeaths(STU_Utils::TextFromInt(PlayerState->GetDeathsNum()));
		PlayerStateRowWidget->SetTeam(STU_Utils::TextFromInt(PlayerState->GetTeamID()));
		PlayerStateRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
	
		PlayerStateBox->AddChild(PlayerStateRowWidget);
	}
}