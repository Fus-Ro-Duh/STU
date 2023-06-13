// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STU_WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

USTU_WeaponFXComponent::USTU_WeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USTU_WeaponFXComponent::PlayImpactVFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;
	auto ImpactSound = DefaultSound;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		ImpactData.NiagaraEffefct,
		Hit.ImpactPoint,
		Hit.ImpactNormal.Rotation());

	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
		ImpactData.DecalData.Material,
		ImpactData.DecalData.Size,
		Hit.ImpactPoint,
		Hit.ImpactNormal.Rotation());
	 
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.Sound, Hit.ImpactPoint);

	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}

}



