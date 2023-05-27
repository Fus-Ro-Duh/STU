// Fill out your copyright notice in the Description page of Project Settings.


#include "STU_GameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "AI/STUAIController.h"
#include "UI/STU_GameHUD.h"
#include "Player/STUPlayerState.h"
#include "STU_Utils.h"
#include "EngineUtils.h"
#include "Components/STURespawnComponent.h"
#include "STUGameInstance.h"

constexpr static int32 MinRoundTimeForRespawn = 10;

ASTU_GameModeBase::ASTU_GameModeBase()
{
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass= ASTU_GameHUD::StaticClass();
	PlayerStateClass = ASTUPlayerState::StaticClass();
}

void ASTU_GameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamsInfo();
	CurrentRound = 1;
	StartRound();

	SetMatchState(ESTUMatchState::InProgress);
}

UClass* ASTU_GameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if(InController && InController->IsA<AAIController>()) return AIPawnClass;

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTU_GameModeBase::Killed(AController* Killer, AController* Victim)
{
	const auto KillerPlayerState = Killer ? Cast<ASTUPlayerState>(Killer->PlayerState) : nullptr;
	const auto VictimPlayerState = Victim ? Cast<ASTUPlayerState>(Victim->PlayerState) : nullptr;
		
	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}

	StartRespawn(Victim);
}

void ASTU_GameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

bool ASTU_GameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const bool SetPause = Super::SetPause(PC, CanUnpauseDelegate);
	
	if (SetPause)
	{
		SetMatchState(ESTUMatchState::Pause);
	}
	return SetPause;
}

bool ASTU_GameModeBase::ClearPause()
{
	const bool ClearPause = Super::ClearPause();

	if (ClearPause)
	{
		SetMatchState(ESTUMatchState::InProgress);
	}
	return ClearPause;
}

void ASTU_GameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(STUAIController);
	}
}

void ASTU_GameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTU_GameModeBase::GameTimerUpdate, 1.0f, true);
}

void ASTU_GameModeBase::GameTimerUpdate()
{

	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			GameOver();
		}
	}
}

void ASTU_GameModeBase::ResetPlayers()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void ASTU_GameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void ASTU_GameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int32 TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;
			
		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;
			
		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");

		SetPlayerColor(Controller);
		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor ASTU_GameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if (TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID-1];
	}
	return GameData.DefaultColor;
}

void ASTU_GameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller) return;

	const auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
	if (!Character) return;

	const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASTU_GameModeBase::LogPlayerInfo()
{
	if (!GetWorld()) return;
	
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->LogInfo();
	}
}

void ASTU_GameModeBase::StartRespawn(AController* Controller)
{
	const auto RespawnAvailable = RoundCountDown >= (MinRoundTimeForRespawn + GameData.RespawnTime);
	if (!RespawnAvailable) return;

	const auto RespawnComponent = STU_Utils::GetSTUPlayerComponent<USTURespawnComponent>(Controller);
	if (!RespawnComponent) return;

	RespawnComponent->Respawn(GameData.RespawnTime);
}

void ASTU_GameModeBase::GameOver()
{
	LogPlayerInfo();

	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}
	SetMatchState(ESTUMatchState::GameOver);
}

void ASTU_GameModeBase::SetMatchState(ESTUMatchState State)
{
	if (MatchState == State) return;
	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}
