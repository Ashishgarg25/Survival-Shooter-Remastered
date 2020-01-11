// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "ConstructorHelpers.h"
#include "Engine.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "SurvivalShooterCharacter.h"

bool bIsPlayerDetected = false;

AEnemyController::AEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sight"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("My Perception Comp")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	bIsPlayerDetected = true;
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsPlayerDetected)
	{
		ASurvivalShooterCharacter* Player = (ASurvivalShooterCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);
		MoveToActor(Player, 2.f);
	}
}

void AEnemyController::OnPossess(APawn * Pawn)
{
	Super::OnPossess(Pawn);
}

FRotator AEnemyController::GetControlRotation() const
{
	return FRotator();
}

void AEnemyController::OnPawnDetected(const TArray<AActor*>& DetectedPawn)
{
	for (size_t i = 0; i < DetectedPawn.Num(); i++)
	{
		DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawn[i]);
	}
	bIsPlayerDetected = true;
}
