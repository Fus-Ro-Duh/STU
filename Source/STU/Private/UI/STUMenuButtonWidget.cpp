// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUMenuButtonWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"

void USTUMenuButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &USTUMenuButtonWidget::OnMainMenu);
	}
}

void USTUMenuButtonWidget::OnMainMenu()
{
	if (!GetWorld()) return;

	const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if (!STUGameInstance) return;

	if (STUGameInstance->GetMenuLevelName().IsNone()) return;

	UGameplayStatics::OpenLevel(this, STUGameInstance->GetMenuLevelName());
}

