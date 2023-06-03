// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STU_AICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class STU_API ASTU_AICharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()
	
public:
	ASTU_AICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviourTreeAsset;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		float HealthVisibilityDistance = 1000.0f;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
	virtual void OnDeath() override;

	virtual void OnHealthChanged(float Health, float HealthDelta) override;

private:
	void UpdateHealthWidgetVisibility();
};
