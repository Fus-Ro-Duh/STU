// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUCoreTypes.h"
#include "STU_GameModeBase.generated.h"

class AAIController;

UCLASS()
class STU_API ASTU_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASTU_GameModeBase();

	FOnMatchStateChangedSignature OnMatchStateChanged;

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	void Killed(AController* Killer, AController* Victim);

	int32 GetCurrentTime() { return RoundCountDown; }
	int32 GetCurrentRound() { return CurrentRound; }
	FGameData GetRoundsNum() { return GameData; }

	void RespawnRequest(AController* Controller);

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

private:
	ESTUMatchState MatchState = ESTUMatchState::WaitingToStart;
	int32 CurrentRound = 1;
	int32 RoundCountDown = 0;
	FTimerHandle GameRoundTimerHandle;

	void SpawnBots();
	void StartRound();
	void GameTimerUpdate();

	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);

	void CreateTeamsInfo();
	FLinearColor DetermineColorByTeamID(int32 TeamID) const;
	void SetPlayerColor(AController* Controller);

	void LogPlayerInfo();
	void StartRespawn(AController* Controller);

	void GameOver();

	void SetMatchState(ESTUMatchState State);
};
