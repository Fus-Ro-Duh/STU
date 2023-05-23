// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUClipsDecorator.generated.h"

class ASTUBase_Weapon;

UCLASS()
class STU_API USTUClipsDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	USTUClipsDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<ASTUBase_Weapon> WeaponType;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
