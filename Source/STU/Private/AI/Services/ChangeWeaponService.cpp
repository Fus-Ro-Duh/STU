// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/ChangeWeaponService.h"
#include "Components/WeaponComponent.h"
#include "AIController.h"
#include "STU_Utils.h"


UChangeWeaponService::UChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void UChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto WeaponComponent = STU_Utils::GetSTUPlayerComponent<UWeaponComponent>(Controller->GetPawn());

		float CurrentProbabily = FMath::FRand();

		if (WeaponComponent && Probability >= CurrentProbabily)
		{
			WeaponComponent->NextWeapon();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

