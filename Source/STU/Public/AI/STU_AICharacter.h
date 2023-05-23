// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STU_AICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class STU_API ASTU_AICharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()
	
public:
	ASTU_AICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviourTreeAsset;

protected:
	virtual void OnDeath() override;
};
