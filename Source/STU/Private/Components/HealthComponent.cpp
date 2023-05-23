
#include "Components/HealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "STU_GameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	}
	
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

	SetHealth(Health-Damage);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	if(IsDead())
	{
		Killed(InstigatedBy);
		OnDeath.Broadcast();
	}
	else if (AutoRegenerate)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UHealthComponent::RegenarateHealth, RegenerateRate, true, RagenerateLag);
	}

	PlayCameraShake();
}

void UHealthComponent::RegenarateHealth()
{
	if (IsDead()) return;
	SetHealth(Health + HealthRegenerated);

	if (IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}

void UHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

bool UHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsHealthFull() || IsDead()) return false;

	SetHealth(Health + HealthAmount);
	return true;
}

bool UHealthComponent::IsHealthFull()
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UHealthComponent::PlayCameraShake()
{
	if (IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void UHealthComponent::Killed(AController* Killer)
{
	if (!GetWorld()) return;

	const auto GameMode = Cast<ASTU_GameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = Cast<APawn>(GetOwner());
	const auto Victim = Player ? Player->Controller : nullptr;

	GameMode->Killed(Killer, Victim);
}
