// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;

UCLASS()
class STU_API ASTUBase_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBase_Weapon();

	FOnClipEmptySignature OnClipEmpty;

	virtual void StartFire();
	virtual void StopFire();

	void ChangeClip();
	bool CanReload() const;

	FWeaponUIData GetUIData() const { return UIData; }
	FAmmoData GetAmmoData() const { return CurrentAmmo; }

	bool TryToAddAmmo(int32 ClipsAmount);
	bool IsAmmoEmpty() const;
	bool IfAmmoFull();

	virtual void Zoom(bool Enabled) {}

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo {15, 10, false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FWeaponUIData UIData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* MuzzleFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* NoAmmoSound;

	virtual void BeginPlay() override;

	virtual void MakeShot();

	FVector GetMuzzleWorldLocation() const;
	bool GetPlayerViewpoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void DecreaseAmmo();

	bool IsClipEmpty() const;

	UNiagaraComponent* SpawnMuzzleFX();

private:
	FAmmoData CurrentAmmo;
};
