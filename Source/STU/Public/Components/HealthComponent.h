#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UCameraShakeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STU_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UHealthComponent();
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const { return Health / MaxHealth; }

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;
	FTimerHandle TimerHandle;

	bool TryToAddHealth(float HealthAmount);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Regenerate")
	bool AutoRegenerate = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Regenerate", meta = (ClampMin = "0.1", ClampMax = "99.0", EditCondition="AutoRegenerate"))
	float HealthRegenerated = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Regenerate", meta = (ClampMin = "0.25", EditCondition = "AutoRegenerate"))
	float RagenerateLag = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Regenerate", meta = (ClampMin = "0.1", EditCondition = "AutoRegenerate"))
	float RegenerateRate = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;

	virtual void BeginPlay() override;
	
private:
	float Health = 0.0f;
	float DamageTime = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
		
	void RegenarateHealth();
	void SetHealth(float NewHealth);

	bool IsHealthFull();

	void PlayCameraShake();

	void Killed(AController* Killer);
};