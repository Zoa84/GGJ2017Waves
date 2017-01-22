// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves.h"
#include "WavesCharacter.h"
#include "EnemyCharacter.h"


#define TO_RADIANS	3.14159 / 180
#define TO_DEGREES	180 / 3.14159


//// Sets default values
//AEnemyCharacter::AEnemyCharacter()
//{
//
//}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Default values
	fSpeed = 1.0f;
	sType = "Red";
	iHealth = 1;
	bDead = false;

	capsuleComp = this->GetCapsuleComponent();
	capsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//capsuleComp->OnComponentBeginOverlap.AddDynamic(this, OnHit);
	SetActorEnableCollision(true);

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnHit");
	OnActorHit.Add(Delegate);

	capsuleComp->OnComponentHit.AddDynamic(this, &AEnemyCharacter::OnHit);
}

// Called every frame
void AEnemyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector vPlayerLoc = playerCharacter->GetActorLocation();	
	
	FVector vHeading = calcHeading(vPlayerLoc);	//Get heading towards player
	AddMovementInput(vHeading * fSpeed);		//Moves towards players position

	vHeading = FVector(vHeading.X, vHeading.Y, 0.f);
	float fAngle = vHeading.HeadingAngle() * TO_DEGREES;
	this->SetActorRotation(FRotator(0.f, fAngle, 0.f));

	if (bDead) this->Destroy();

	//Check if dead
	if (iHealth <= 0) bDead = true;
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

void AEnemyCharacter::OnHit(AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor->GetClass()->IsChildOf(AWavesCharacter::StaticClass())) {
		bDead = true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Hit %f"), 1);
}

bool AEnemyCharacter::isDead() {
	return bDead;
}