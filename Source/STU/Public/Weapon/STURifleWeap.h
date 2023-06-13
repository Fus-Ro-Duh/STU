// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeap.generated.h"

class USTU_WeaponFXComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class STU_API ASTURifleWeap : public ASTUBase_Weapon
{
	GENERATED_BODY()

public:
	ASTURifleWeap();

	virtual void StartFire() override;
	virtual void StopFire() override;
	virtual void Zoom(bool Enabled) override;

protected:
	virtual void BeginPlay() override;
	virtual void MakeShot() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FOVZoomAngle = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	float TimeBetweenShots = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float HitDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float BulletSpread = 1.5f;

	UPROPERTY(EditAnywhere, Category = "VFX")
	USTU_WeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* TraceFX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	FString TraceTargetName = "TraceTarget";

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;

	void MakeDamage(const FHitResult& HitResult);
	void InitMuzzleFX();
	void SetMuzzleVisibility(bool Visible);
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

	AController* GetController() const;
	float DefaultCameraFOV = 90.0f;
};
