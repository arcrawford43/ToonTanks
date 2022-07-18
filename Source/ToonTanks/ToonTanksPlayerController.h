// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanksPlayerController.generated.h"

struct Metrics
{
	float mDistanceMoved = 0;
	float mTimeTaken = 0;
	int32 mShotsFired = 0;//
	float mShotsHit = 0;//
	float mShotAccuracy = 0;
	int32 mTowersKilled = 0;//
};


UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetPlayerEnabledState(bool bPlayerEnabled);
	Metrics mMetrics;
};
