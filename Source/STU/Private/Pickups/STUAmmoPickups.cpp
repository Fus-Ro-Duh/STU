// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickups/STUAmmoPickups.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "STU_Utils.h"


DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASTUAmmoPickups::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STU_Utils::GetSTUPlayerComponent<UHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = STU_Utils::GetSTUPlayerComponent<UWeaponComponent>(PlayerPawn);
	if (!WeaponComponent) return false;

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
