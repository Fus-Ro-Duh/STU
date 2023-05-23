// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUSpectatorWidget.h"
#include "Components/STURespawnComponent.h"
#include "STU_Utils.h"

bool USTUSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
    const auto RespawnComponent = STU_Utils::GetSTUPlayerComponent<USTURespawnComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

    CountDownTime = RespawnComponent->GetRespawnCoundDown();
    return true;
}
