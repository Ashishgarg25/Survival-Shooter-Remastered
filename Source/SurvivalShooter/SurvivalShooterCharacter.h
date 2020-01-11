// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivalShooterCharacter.generated.h"

UCLASS(config=Game)
class ASurvivalShooterCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	ASurvivalShooterCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* PlayerDeathAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* PlayerHurtAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* GunShotAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundCue* PlayerDeathAudioCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundCue* PlayerHurtAudioCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundCue* GunShotAudioCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float CurrentHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHp;

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetCurrentHp();

	UFUNCTION(BlueprintCallable, Category = "Health")
		float UpdateHp(float HpTaken);

	UFUNCTION()
		void LookRotation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AActor> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isFiring;

	UFUNCTION()
		void SpawnWeapon();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	void Shoot();

	void EndShoot();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

