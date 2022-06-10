// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include <assert.h>
#include "TimerManager.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	assert(Tank);

	FireRangeSquared = FireRange * FireRange;

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
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
