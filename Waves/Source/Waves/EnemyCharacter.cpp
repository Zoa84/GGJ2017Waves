// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves.h"
#include "EnemyCharacter.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector vPlayerLoc = playerCharacter->GetActorLocation();	
	
	FVector vHeading = calcHeading(vPlayerLoc);	//Get heading towards player
	AddMovementInput(vHeading);			//Moves towards players position
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

FVector AEnemyCharacter::calcHeading(FVector target)
{
	FVector vPos = this->GetActorLocation();
	FVector vDiff = vPos - target;
	float fDistance = vDiff.Size();	//Magnitude

	FVector vHeading = FVector(
		(target.X - vPos.X) / fDistance,
		(target.Y - vPos.Y) / fDistance,
		(target.Z - vPos.Z) / fDistance);
	vHeading.Normalize();

	return vHeading;
}

