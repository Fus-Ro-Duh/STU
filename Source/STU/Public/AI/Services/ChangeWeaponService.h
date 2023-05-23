// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ChangeWeaponService.generated.h"

UCLASS()
class STU_API UChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:
	UChangeWeaponService();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Probability = 0.8f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
