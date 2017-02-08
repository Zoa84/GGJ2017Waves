// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves.h"
#include "WavesCharacter.h"
#include "Bullet_Pawn.h"
#include "EnemyCharacter.h"

#define TO_RADIANS	3.14159 / 180
#define TO_DEGREES	180 / 3.14159

// Sets default values
ABullet_Pawn::ABullet_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Box Component
	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = boxComponent;
	boxComponent->InitBoxExtent(FVector(9.0f, 32.0f, 32.0f));
	boxComponent->SetCollisionProfileName(TEXT("NoCollision"));
	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet_Pawn::OnOverlap);
	boxComponent->OnComponentHit.AddDynamic(this, &ABullet_Pawn::OnHit);
	
	//Create static mesh component
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	fSpeed = 5.0f;
	sType = "None";

	Material_Red = new ConstructorHelpers::FObjectFinder <UMaterialInterface>(TEXT("Material'/Game/red_wave_Mat.red_wave_Mat'"));
	Material_Green = new ConstructorHelpers::FObjectFinder <UMaterialInterface>(TEXT("Material'/Game/green_wave_Mat.green_wave_Mat'"));
	Material_Blue = new ConstructorHelpers::FObjectFinder <UMaterialInterface>(TEXT("Material'/Game/blue_wave_Mat.blue_wave_Mat'"));
}

// Called when the game starts or when spawned
void ABullet_Pawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet_Pawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	//Manually set new location
	this->SetActorLocation(this->GetActorLocation() + (vHeading * fSpeed));
	this->SetActorRotation(FRotator(0.f, vHeading.HeadingAngle() * TO_DEGREES, 0.f));
	this->SetActorScale3D(this->GetActorScale3D() * 1.005f);
	boxComponent->SetWorldScale3D(RootComponent->GetComponentScale());
}

// Called to bind functionality to input
void ABullet_Pawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void ABullet_Pawn::SetHeading(FVector f) {
	vHeading = f;
	vHeading.Normalize();
	vHeading = vHeading.RotateAngleAxis(270.f, FVector(0.f, 0.f, 1.f));
};

void ABullet_Pawn::SetWeapons(bool b1, bool b2, bool b3) {
	if (b1)
	{
		sType = "Red";
		BulletMesh->SetMaterial(0, Material_Red->Object);
	}
	else if (b2)
	{
		sType = "Green";
		BulletMesh->SetMaterial(0, Material_Green->Object);
	}
	else if (b3)
	{
		sType = "Blue";
		BulletMesh->SetMaterial(0, Material_Blue->Object);
	}
};

FString ABullet_Pawn::getWeaponType() {
	return sType;
}
void ABullet_Pawn::OnOverlap(UPrimitiveComponent * OverlappingComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT"));
	if (OtherActor->IsA(AEnemyCharacter::StaticClass())) {
		BulletMesh->DestroyComponent();
		this->Destroy();
	}
}

void ABullet_Pawn::OnHit(UPrimitiveComponent * HitComp, AActor * Actor, UPrimitiveComponent * Other, FVector Impulse, const FHitResult & HitResult)
{
	if (Actor->IsA(AEnemyCharacter::StaticClass())) {
		BulletMesh->DestroyComponent();
		this->Destroy();
	}
}
