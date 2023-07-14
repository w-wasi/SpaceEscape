// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileShooter.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class AProjectile;


UCLASS()
class TWODRUNNERCPP_API AProjectileShooter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileShooter();

	void ShootProjectile();
	void SpawnProjectile();

	AProjectile* SpawnTop();
	AProjectile* SpawnBottom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileSpawner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* SpawnPositionTop;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* SpawnPositionBottom;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBPClass;

private:

	int32 MinRange = 0;
	int32 MaxRange = 4;

	float NextSpawnTime = 0.f;
	double LastSpawnTime = 0;
	double TimeElapsed = 0;
	bool bCanShootProjectile = false;

};
