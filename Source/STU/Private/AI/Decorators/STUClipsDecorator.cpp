// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/STUClipsDecorator.h"
#include "AIController.h"
#include "STU_Utils.h"
#include "Weapon/STULauncherWeapon.h"
#include "Components/WeaponComponent.h"

USTUClipsDecorator::USTUClipsDecorator()
{
	NodeName = "Clips Left";
}

bool USTUClipsDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto WeaponComponent = STU_Utils::GetSTUPlayerComponent<UWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent) return false;

	for (const auto Weapon : WeaponComponent->GetWeapons())
	{
		if (Weapon->IsA(WeaponType))
		{
			return !Weapon->IfAmmoFull();
		}
	}
	return false;
}
