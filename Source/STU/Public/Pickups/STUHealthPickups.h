// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickups.h"
#include "STUHealthPickups.generated.h"


UCLASS()
class STU_API ASTUHealthPickups : public ASTUBasePickups
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	float HealthAmount = 35;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
