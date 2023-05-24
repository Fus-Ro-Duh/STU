#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUGameOverWidget.generated.h"

class UVerticalBox;

UCLASS()
class STU_API USTUGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStateBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStateRowWidgetClass;

private:
	void OnMatchStateChanged(ESTUMatchState State);
	void UpdatePlayersState();
};
