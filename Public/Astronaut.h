// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Astronaut.generated.h"

/**
 * 
 */

class USpringArmComponent;
class UCameraComponent;
class UProjectileShootingComponent;
class AProjectileShooter;
class USoundCue;
class UUserWidget;


UCLASS()
class TWODRUNNERCPP_API AAstronaut : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAstronaut();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Setup")
	void PlayDeadAnimation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Setup")
	void PlayRunAnimation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Setup")
	void PlayCrouchAnimation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Setup")
	void PlayJumpAnimation();

	UPROPERTY(EditAnywhere)
	USoundCue* SoundDeath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	AProjectileShooter* RockShooter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Score;

	UPROPERTY(EditAnywhere, Category = "UI HUD")
	TSubclassOf<UUserWidget> WBP_Score_Class;

	UUserWidget* ScoreWidget;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Crouch();
	void StopCrouching();

	void Jump();
	void StopJumping();

	void UpdatePlayerScore();

private:

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
