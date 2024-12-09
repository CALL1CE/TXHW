// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPS_AndroidGameMode.generated.h"

UCLASS(minimalapi)
class AFPS_AndroidGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPS_AndroidGameMode();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Duration of the game in seconds
	UPROPERTY(EditDefaultsOnly, Category = "Game Rules")
	float GameDuration;

	// Function to handle game ending
	void EndGame();

private:
	FTimerHandle GameTimerHandle; // ¼ÆÊ±Æ÷¾ä±ú
};



