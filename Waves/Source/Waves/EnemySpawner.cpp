// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves.h"
#include "EnemySpawner.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	iMaxEnemy = 1;
	iSpawnCounter = 0;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (iSpawnCounter < iMaxEnemy) {
		spawn();
		iSpawnCounter++;
	}
}

void AEnemySpawner::spawn() {
	if (Enemy != NULL) {
		UWorld* const World = GetWorld();

		if (World) {

			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;

			FVector vLocation = this->GetActorLocation();

			FRotator rotation;
			rotation.Yaw = 0.0f;
			rotation.Pitch = 0.0f;
			rotation.Roll = 0.0f;

			World->SpawnActor<AEnemyCharacter>(Enemy, vLocation, rotation, spawnParams);
		}
	}

}