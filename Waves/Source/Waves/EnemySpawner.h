// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyCharacter.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class WAVES_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
protected:
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemyCharacter> Enemy;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	int iStartTimer;

private:
	void spawn();

	int iMaxTimer;
	int iTimer;
	float fMulti;
	int iSpawnCounter;
};
