// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickUpCanBeTaken.generated.h"



UCLASS()
class STU_API UEnvQueryTest_PickUpCanBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()
	
public:
	UEnvQueryTest_PickUpCanBeTaken(const FObjectInitializer& FObjectInitializer);

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
