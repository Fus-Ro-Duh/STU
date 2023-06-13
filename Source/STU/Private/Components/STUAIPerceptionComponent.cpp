// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STU_Utils.h"
#include "Components/HealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0)
	{
		GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);
		if (PercieveActors.Num() == 0) return nullptr;
	}
	
	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* Best = nullptr;

	for (const auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = STU_Utils::GetSTUPlayerComponent<UHealthComponent>(PercieveActor);

		const auto PercievePawn = Cast<APawn>(PercieveActor);
		const auto AreEnemies = PercievePawn && STU_Utils::AreEnemies(Controller, PercievePawn->Controller);

		if (HealthComponent && !HealthComponent->IsDead() && AreEnemies)
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				Best = PercieveActor;
			}
		}
	}

	return Best;
}
