// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickups.h"
#include "STUAmmoPickups.generated.h"

class ASTUBase_Weapon;

UCLASS()
class STU_API ASTUAmmoPickups : public ASTUBasePickups
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 ClipsAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<ASTUBase_Weapon> WeaponType;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
