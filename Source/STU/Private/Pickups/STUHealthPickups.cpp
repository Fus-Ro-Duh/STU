// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickups/STUHealthPickups.h"
#include "Components/HealthComponent.h"
#include "STU_Utils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASTUHealthPickups::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STU_Utils::GetSTUPlayerComponent<UHealthComponent>(PlayerPawn);
	if(!HealthComponent) return false;

	return HealthComponent->TryToAddHealth(HealthAmount);
}
