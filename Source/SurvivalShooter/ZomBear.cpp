// Fill out your copyright notice in the Description page of Project Settings.


#include "ZomBear.h"
#include "SurvivalShooterCharacter.h"
#include "Engine.h"
#include "SurvivalShooterGameMode.h"
#include "Components/AudioComponent.h"

AZomBear::AZomBear()
{
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AZomBear::OnEnemyOverlap1);

	EnemyShotAudio1 = CreateDefaultSubobject<UAudioComponent>(TEXT("EnemyShot Audio1"));

	EnemyDeathAudio1 = CreateDefaultSubobject<UAudioComponent>(TEXT("EnemyDeath Audio1"));
}

float AZomBear::GetCurrentHp1()
{
	return (CurrentHp / MaxHp);
}

float AZomBear::UpdateHp1(float HpTaken)
{
	CurrentHp -= HpTaken;

	if (CurrentHp >= MaxHp) {
		CurrentHp = MaxHp;
	}
	else if (CurrentHp < MaxHp)
	{
		EnemyShotAudio1->SetSound(EnemyShotAudioCue1);
		EnemyShotAudio1->Play();

		if (CurrentHp <= 0.0f) {

			UE_LOG(LogTemp, Warning, TEXT("No ZomBear HP"));

			EnemyDeathAudio1->SetSound(EnemyDeathAudioCue1);
			EnemyDeathAudio1->Play();

			FTransform trans = GetActorTransform();
			FActorSpawnParameters SpawnParams;

			GetWorld()->SpawnActor(HpDrop, &trans, SpawnParams);

			ASurvivalShooterGameMode* GameMode = (ASurvivalShooterGameMode*)GetWorld()->GetAuthGameMode();
			GameMode->ScoreCount(5);

			Destroy();
		}
	}

	return CurrentHp;
}


void AZomBear::OnEnemyOverlap1(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResults)
{
	UE_LOG(LogTemp, Warning, TEXT("Collsion Working"));

	if (OverlappedComp != NULL && OtherComp != NULL && OtherActor != this)
	{
		ASurvivalShooterCharacter* Player = (ASurvivalShooterCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

		if (OtherActor == Player) {
			float Damage = FMath::RandRange(50, 100);
			Player->UpdateHp(Damage);
			UE_LOG(LogTemp, Warning, TEXT("Player Collsion Working"));
		}
		else if (OtherActor->ActorHasTag("Bullet")) {
			float Dmg = FMath::RandRange(100, 150);
			UpdateHp1(Dmg);
			UE_LOG(LogTemp, Warning, TEXT("Bullet Collsion Working"));

			OtherActor->Destroy();
		}
	}
}

// Called when the game starts or when spawned
void AZomBear::BeginPlay()
{
	Super::BeginPlay();

	MaxHp = 500.f;
	CurrentHp = MaxHp;
}


