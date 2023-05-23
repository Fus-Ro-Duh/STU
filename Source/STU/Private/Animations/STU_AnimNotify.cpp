// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/STU_AnimNotify.h"

void USTU_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}
