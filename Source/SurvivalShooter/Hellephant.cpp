// Fill out your copyright notice in the Description page of Project Settings.


#include "Hellephant.h"
#include "SurvivalShooterCharacter.h"
#include "Engine.h"
#include "SurvivalShooterGameMode.h"
#include "Components/AudioComponent.h"

AHellephant::AHellephant()
{
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AHellephant::OnEnemyOverlap2);

	EnemyShotAudio2 = CreateDefaultSubobject<UAudioComponent>(TEXT("EnemyShot Audio2"));

	EnemyDeathAudio2 = CreateDefaultSubobject<UAudioComponent>(TEXT("EnemyDeath Audio2"));
}

float AHellephant::GetCurrentHp2()
{
	Super::GetCurrentHp();
	return (CurrentHp / MaxHp);
}

float AHellephant::UpdateHp2(float HpTaken)
{
	Super::UpdateHp(HpTaken);

	CurrentHp -= HpTaken;

	if (CurrentHp >= MaxHp) {
		CurrentHp = MaxHp;
	}
	else if (CurrentHp < MaxHp)
	{
		EnemyShotAudio2->SetSound(EnemyShotAudioCue2);
		EnemyShotAudio2->Play();

		if (CurrentHp <= 0.0f) {

			UE_LOG(LogTemp, Warning, TEXT("No Hellephant HP"));

			EnemyDeathAudio2->SetSound(EnemyDeathAudioCue2);
			EnemyDeathAudio2->Play();

			FTransform trans = GetActorTransform();
			FActorSpawnParameters SpawnParams;

			GetWorld()->SpawnActor(HpDrop, &trans, SpawnParams);

			ASurvivalShooterGameMode* GameMode = (ASurvivalShooterGameMode*)GetWorld()->GetAuthGameMode();
			GameMode->ScoreCount(15);

			Destroy();
		}
	}

	return CurrentHp;
}


void AHellephant::OnEnemyOverlap2(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResults)
{
	Super::OnEnemyOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResults);

	if (OverlappedComp != NULL && OtherComp != NULL && OtherActor != this)
	{
		ASurvivalShooterCharacter* Player = (ASurvivalShooterCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

		if (OtherActor == Player) {
			float Damage = FMath::RandRange(150, 200);
			Player->UpdateHp(Damage);
		}

		else if (OtherActor->ActorHasTag("Bullet")) {
			float Dmg = FMath::RandRange(100, 150);
			UpdateHp2(Dmg);

			OtherActor->Destroy();
		}
	}
}

// Called when the game starts or when spawned
void AHellephant::BeginPlay()
{
	Super::BeginPlay();

	MaxHp = 1000.f;
	CurrentHp = MaxHp;
}
