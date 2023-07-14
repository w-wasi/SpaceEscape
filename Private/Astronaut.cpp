// Fill out your copyright notice in the Description page of Project Settings.


#include "Astronaut.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Sound/SoundCue.h"
#include "PaperFlipbookComponent.h"
#include "ProjectileShooter.h"



AAstronaut::AAstronaut(){
	
	PrimaryActorTick.bCanEverTick = true;

	// Params are (radius, half height)
	GetCapsuleComponent()->InitCapsuleSize(11.0f, 19.0f);

	/*Spring Arm Settings*/

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 120.0f;

	//FRotator(Y, Z, X)
	CameraBoom->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));


	// *Camera Settings*

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	
	FollowCamera->ProjectionMode = ECameraProjectionMode::Orthographic;
	FollowCamera->OrthoWidth = 250.0f;

	FPostProcessSettings CameraBrightSettings;

	CameraBrightSettings.AutoExposureMaxBrightness = 0.8f;
	CameraBrightSettings.AutoExposureMinBrightness = 0.8f;
	CameraBrightSettings.bOverride_AutoExposureMaxBrightness = true;
	CameraBrightSettings.bOverride_AutoExposureMinBrightness = true;

	FollowCamera->PostProcessSettings = CameraBrightSettings;

	Score = 0;

	bDead = false;

	GetCharacterMovement()->JumpZVelocity = 250.0f;
	GetCharacterMovement()->CrouchedHalfHeight = 0.0f;
	
}

void AAstronaut::BeginPlay(){

	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAstronaut::OnOverlap);

	// Adding score widget
	if (WBP_Score_Class != NULL) {
		ScoreWidget = CreateWidget(GetWorld(), WBP_Score_Class);
		ScoreWidget->AddToViewport();

	}

	//Updating Score
	FTimerHandle UnUsedHandle;
	GetWorldTimerManager().SetTimer(UnUsedHandle, this, &AAstronaut::UpdatePlayerScore, 1.0f, true);

}

void AAstronaut::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (bDead) {
		PlayDeadAnimation();
	
	}
	else {
		
		if (GetCharacterMovement()->IsMovingOnGround() && GetCharacterMovement()->IsCrouching()) {
			PlayCrouchAnimation();
		}
		else if (GetCharacterMovement()->IsMovingOnGround() && !GetCharacterMovement()->IsCrouching()) {
			PlayRunAnimation();
		}
		else if (!GetCharacterMovement()->IsMovingOnGround() && GetCharacterMovement()->IsFalling()) {
			PlayJumpAnimation();
		}
	}

}

void AAstronaut::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AAstronaut::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AAstronaut::StopJumping);

	PlayerInputComponent->BindAction("Slide", IE_Pressed, this, &AAstronaut::Crouch);
	PlayerInputComponent->BindAction("Slide", IE_Released, this, &AAstronaut::StopCrouching);



}

void AAstronaut::Crouch()
{
	ACharacter::Crouch();

	GetSprite()->SetRelativeLocation(FVector(0.0 , 0.0 , -5.0));
}

void AAstronaut::StopCrouching()
{
	ACharacter::UnCrouch();

	GetSprite()->SetRelativeLocation(FVector(0.0, 0.0, -3.0));
}

void AAstronaut::Jump()
{
	ACharacter::Jump();
}

void AAstronaut::StopJumping()
{
	ACharacter::StopJumping();
}

void AAstronaut::UpdatePlayerScore(){

	if (!bDead) {	
			Score++;
	}
}

void AAstronaut::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Rock")) {
		UGameplayStatics::PlaySound2D(this, SoundDeath);
		bDead = true;
	}
}


