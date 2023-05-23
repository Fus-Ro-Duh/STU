// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STU_CharacterMovementComponent.h"
#include "Player/STUBaseCharacter.h"

float USTU_CharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(GetPawnOwner());
	return Player&&Player->Run()? MaxSpeed*RunModifier: MaxSpeed;
}
