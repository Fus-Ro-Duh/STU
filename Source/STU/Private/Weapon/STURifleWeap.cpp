// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STURifleWeap.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "STU_WeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ASTURifleWeap::ASTURifleWeap()
{
	WeaponFXComponent = CreateDefaultSubobject<USTU_WeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeap::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);
}

void ASTURifleWeap::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	FVector TraceFXEnd = TraceEnd;
	if (HitResult.bBlockingHit)
	{
		TraceFXEnd = HitResult.ImpactPoint;
		MakeDamage(HitResult);
		WeaponFXComponent->PlayImpactVFX(HitResult);
	}
	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
	DecreaseAmmo();
	SpawnMuzzleFX();
}

void ASTURifleWeap::StartFire()
{
	//InitMuzzleFX();
	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeap::MakeShot, TimeBetweenShots, true);
}

void ASTURifleWeap::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	//SetMuzzleVisibility(false);
}

bool ASTURifleWeap::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewpoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ASTURifleWeap::MakeDamage(const FHitResult& HitResult)
{
	AActor* HitActor = HitResult.GetActor();
	if (HitActor == nullptr) return;

	HitActor->TakeDamage(HitDamage, FDamageEvent(), GetController(), this);
}

void ASTURifleWeap::InitMuzzleFX()
{
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}
	SetMuzzleVisibility(true);
}

void ASTURifleWeap::SetMuzzleVisibility(bool Visible)
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!Visible);
		MuzzleFXComponent->SetVisibility(Visible, true);
	}
}

void ASTURifleWeap::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
	if (TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}

AController* ASTURifleWeap::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}