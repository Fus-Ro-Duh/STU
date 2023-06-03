// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUBaseWidget.generated.h"

UCLASS()
class STU_API USTUBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Show();

protected:
	UPROPERTY(meta = (BindWidgetanim), Transient)
	UWidgetAnimation* ShowAnimation;
};
