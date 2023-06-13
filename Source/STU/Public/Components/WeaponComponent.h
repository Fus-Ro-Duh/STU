// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ASTUBase_Weapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STU_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();
	
	virtual void StartFire();
	void StopFire();
	virtual void NextWeapon();
	void Reload();

	bool TryToAddAmmo(TSubclassOf<ASTUBase_Weapon> WeaponType, int32 ClipsAmount);

	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetAmmoData(FAmmoData& AmmoData) const;

	TArray<ASTUBase_Weapon*> GetWeapons();

	void Zoom(bool Enabled);

protected:

	int32 CurrentWeaponIndex = 0;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray <FWeaponData> WeaponData;

	UPROPERTY()
	ASTUBase_Weapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBase_Weapon*> Weapons;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	bool CanEquip() const;
	bool CanFire() const;

	void EquipWeapon(int32 WeaponIndex);

private:
	void SpawnWeapons();

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage;

	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;

	void AttachToWeaponSocket(ASTUBase_Weapon* Weapon, USceneComponent* SceneComponent, FName& SocketName);

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanReload() const;

	void OnEmptyClip(ASTUBase_Weapon* AmmoEmptyWeapon);
	void ChangeClip();
};
