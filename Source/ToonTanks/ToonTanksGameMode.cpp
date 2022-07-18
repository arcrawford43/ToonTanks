// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Died"));
		Tank->HandleDestruction();
		if (Tank->GetPlayerController())
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(ToonTanksPlayerController->mMetrics.mTowersKilled);
	}
	else if(ATower* DestroyTower = Cast<ATower>(DeadActor))
	{
		++(ToonTanksPlayerController->mMetrics.mTowersKilled);
		DestroyTower->HandleTowerDeath();
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	check(ToonTanksPlayerController);
	ToonTanksPlayerController->SetPlayerEnabledState(false);
	FTimerHandle PlayerEnableTimerHandle;
	FTimerDelegate PLayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
	GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PLayerEnableTimerDelegate, StartDelay, false);
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}