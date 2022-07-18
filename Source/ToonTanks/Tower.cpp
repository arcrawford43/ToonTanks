// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include <assert.h>
#include "TimerManager.h"
#include "HealthComponent.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	assert(Tank);

	FireRangeSquared = FireRange * FireRange;

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
	Location = GetActorLocation();

	TArray<UHealthComponent*> HealthComps;
	GetComponents<UHealthComponent> (HealthComps);
	assert(HealthComps[0]);
	Health = HealthComps[0];
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	assert(Tank);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::HandleTowerDeath()
{
	SetActorLocation({ 0.f, 0.f, -1000.f });
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ATower::HandleTowerRespawn, RespawnTime, false);
}

void ATower::HandleTowerRespawn()
{
	Health->Health = Health->MaxHealth;
	SetActorLocation(Location);
}

void ATower::CheckFireCondition()
{

	if (InFireRange())
	{
		Fire();
	}
}

inline bool ATower::InFireRange()
{
	float DistanceSquared = FVector::DistSquared(GetActorLocation(), Tank->GetActorLocation());

	return DistanceSquared <= FireRangeSquared;
}
