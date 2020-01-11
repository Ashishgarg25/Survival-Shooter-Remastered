// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SurvivalShooterGameMode.h"
#include "SurvivalShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"
//#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "MySaveGame.h"
#include "Engine.h"

ASurvivalShooterGameMode::ASurvivalShooterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	BgAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Background Audio"));
}

void ASurvivalShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	Score = 0;

	BgAudio->SetSound(BgAudioCue);
	BgAudio->Play();

	/*if (CharacterWidget != nullptr) {
		CurrentCharacterWidget = CreateWidget<UUserWidget>(GetWorld(), CharacterWidget, NAME_None);
	}

	if (CurrentCharacterWidget != nullptr) {
		CurrentCharacterWidget->AddToViewport();
	}*/

	SpawnEnemies();
}

void ASurvivalShooterGameMode::SpawnEnemies()
{
	int SpawnPointRange = FMath::RandRange(0, 7);

	FVector loc = SpawnPoints[SpawnPointRange].GetLocation();

	FRotator rot = SpawnPoints[SpawnPointRange].GetRotation().Rotator();

	FActorSpawnParameters SpawnParams;

	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	int EnemyVal = FMath::RandRange(0, 2);

	if (EnemyVal == 0) 
	{
		GetWorld()->SpawnActor(Enemy1, &loc, &rot, SpawnParams);
	}
	else if(EnemyVal == 1)
	{
		GetWorld()->SpawnActor(Enemy2, &loc, &rot, SpawnParams);
	}
	else if (EnemyVal == 2)
	{
		GetWorld()->SpawnActor(Enemy3, &loc, &rot, SpawnParams);
	}

	GetWorld()->GetTimerManager().SetTimer(DelayHandler, this, &ASurvivalShooterGameMode::SpawnEnemies, 1.5f, true, 3.f);
}

void ASurvivalShooterGameMode::ScoreCount(int Val)
{
	Score += Val;
}

void ASurvivalShooterGameMode::SaveGame()
{
	UMySaveGame* SaveGameInst = (UMySaveGame*)UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass());

	SaveGameInst->HighScore = Score;

	UGameplayStatics::SaveGameToSlot(SaveGameInst, TEXT("MySlot"), 0);
}

void ASurvivalShooterGameMode::LoadGame()
{
	UMySaveGame* SaveGameInst = (UMySaveGame*)UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass());

	SaveGameInst = (UMySaveGame*)UGameplayStatics::LoadGameFromSlot(TEXT("MySlot"), 0);

	if (Score > SaveGameInst->HighScore) {
		SaveGameInst->HighScore = Score;
	}

	UGameplayStatics::SaveGameToSlot(SaveGameInst, TEXT("MySlot"), 0);
}