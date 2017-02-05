// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves.h"
#include "Bullet_Pawn.h"
#include "WavesCharacter.h"
#include "EnemyCharacter.h"


#define TO_RADIANS	3.14159 / 180
#define TO_DEGREES	180 / 3.14159


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Material_Red = new ConstructorHelpers::FObjectFinder <UMaterialInterface>(TEXT("Material'/Game/Assets/Material_HunterOrange.Material_HunterOrange'"));
	Material_Green = new ConstructorHelpers::FObjectFinder <UMaterialInterface>(TEXT("Material'/Game/Assets/Texture_Tree_01.Texture_Tree_01'"));
	Material_Blue = new ConstructorHelpers::FObjectFinder <UMaterialInterface>(TEXT("Material'/Game/Assets/Textures_Pyro.Textures_Pyro'"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create static mesh component

	//Default values
	fSpeed = 1.0f;

	//TODO Set randomly to r, g or b
	float random = FMath::RandRange(0.f, 1.f);

	if (random <= 0.33f)
	{
		sType = "Red";
	}
	else if (random <= 0.67f)
	{
		sType = "Green";
	}
	else if (random <= 1.f)
	{
		sType = "Blue";
	}

	iHealth = 1;
	bDead = false;

	capsuleComp = this->GetCapsuleComponent();
	capsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetActorEnableCollision(true);

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnHit");
	OnActorHit.Add(Delegate);

	

	if (sType == "Red")
	{
		this->GetMesh()->SetMaterial(0, Material_Red->Object);
	}
	if (sType == "Green")
	{
		this->GetMesh()->SetMaterial(0, Material_Green->Object);
	}
	if (sType == "Blue")
	{
		this->GetMesh()->SetMaterial(0, Material_Blue->Object);
	}
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

	//UE_LOG(LogTemp, Warning, TEXT("Angle: %f"), fAngle);

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
		//bDead = true;
	}
	else if (OtherActor->GetClass()->IsChildOf(ABullet_Pawn::StaticClass())) {
		ABullet_Pawn* bullet = static_cast<ABullet_Pawn*>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Hit %f"), 1.f);
		if (bullet->getWeaponType() == this->sType) {
			bDead = true;
			this->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Hit %f"), 2.f);
		}
	}
	
}

bool AEnemyCharacter::isDead() {
	return bDead;
}

void AEnemyCharacter::takeDamage(int damage) {
	iHealth -= damage;
}