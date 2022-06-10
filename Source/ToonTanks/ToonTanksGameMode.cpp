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
	}
	else if(ATower* DestroyTower = Cast<ATower>(DeadActor))
	{
		DestroyTower->HandleDestruction();
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	check(ToonTanksPlayerController);
	ToonTanksPlayerController->SetPlayerEnabledState(false);
	FTimerHandle PlayerEnableTimerHandle;
	FTimerDelegate PLayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
	GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PLayerEnableTimerDelegate, StartDelay, false);
}