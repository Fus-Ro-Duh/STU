// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/STUBasePickups.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

ASTUBasePickups::ASTUBasePickups()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

bool ASTUBasePickups::CanBeTaken() const
{
	return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

void ASTUBasePickups::BeginPlay()
{
	Super::BeginPlay();
	
	check(CollisionComponent);
	GenerateRotationYaw();
}

void ASTUBasePickups::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}
}

void ASTUBasePickups::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}

bool ASTUBasePickups::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void ASTUBasePickups::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
	}
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickups::Respawn, RespawnTime);
}

void ASTUBasePickups::Respawn()
{
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GenerateRotationYaw();
}

void ASTUBasePickups::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0 : -1.0;
	RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}

