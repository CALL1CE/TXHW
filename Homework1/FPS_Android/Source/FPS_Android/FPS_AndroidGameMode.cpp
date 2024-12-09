// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_AndroidGameMode.h"
#include "FPS_AndroidCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPS_AndroidGameMode::AFPS_AndroidGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	// Default game duration is 15 seconds
	GameDuration = 15.0f;
}

void AFPS_AndroidGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Start a timer that will call EndGame after GameDuration seconds
	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(
			GameTimerHandle,
			this,
			&AFPS_AndroidGameMode::EndGame,
			GameDuration,
			false
		);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get valid UWorld instance!"));
	}
}

void AFPS_AndroidGameMode::EndGame()
{
	// Logic to end the game, for example:
	UE_LOG(LogTemp, Warning, TEXT("Game Over! Time's up."));
	// Get the player character
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		AFPS_AndroidCharacter* PlayerCharacter = Cast<AFPS_AndroidCharacter>(PlayerController->GetPawn());
		if (PlayerCharacter)
		{
			// Get the player's score
			int32 PlayerScore = PlayerCharacter->GetScore();
			UE_LOG(LogTemp, Warning, TEXT("Player's final score: %d"), PlayerScore);
			// ´òÓ¡µ½ÆÁÄ»
			if (GEngine)
			{
				FString ScoreMessage = FString::Printf(TEXT("Player's final score: %d"), PlayerScore);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, ScoreMessage);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get valid PlayerController instance!"));
	}

}
