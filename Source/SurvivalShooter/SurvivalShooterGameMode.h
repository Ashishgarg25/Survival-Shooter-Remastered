// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivalShooterGameMode.generated.h"

UCLASS(minimalapi)
class ASurvivalShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASurvivalShooterGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* BgAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundCue* BgAudioCue;

	FTimerHandle DelayHandler;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf <class AActor> Enemy1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf <class AActor> Enemy2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf <class AActor> Enemy3;

	UFUNCTION()
		void SpawnEnemies();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int CurrentHighScore;

	/*UPROPERTY(EditDefaultsOnly, Category = "Health")
		TSubclassOf<class UUserWidget> CharacterWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UUserWidget* CurrentCharacterWidget;*/

	UFUNCTION()
		void ScoreCount(int Val);

	UFUNCTION()
		void SaveGame();

	UFUNCTION(BlueprintCallable)
		void LoadGame();

protected:

	void BeginPlay() override;
};



