// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves.h"
#include "WavesCharacter.h"
#include "Bullet_Pawn.h"

#define TO_RADIANS	3.14159 / 180
#define TO_DEGREES	180 / 3.14159

// Sets default values
ABullet_Pawn::ABullet_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create static mesh component
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	RootComponent = BulletMesh;

	fSpeed = 5.0f;

}

// Called when the game starts or when spawned
void ABullet_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
	

	//vHeading = FVector(MousePosition.X - (ViewportSize.X / 2), MousePosition.Y - (ViewportSize.Y / 2), 0.f);
	//vHeading = FVector(1.f, 0.f, 0.f);

	//Set the angle of the created bullet
	//float fAngle = vHeading.HeadingAngle() * TO_DEGREES;
	//this->SetActorRotation(FRotator(0.f, fAngle, 0.f));
}

// Called every frame
void ABullet_Pawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//UE_LOG(LogTemp, Warning, TEXT("TEST: %f %f"), vHeading.X, vHeading.Y);
	
	//Set Viewport Size
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	//Mouse positions
	//FVector2D MousePosition;

	//ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	//FVector test = (AWavesCharacter*)playerCharacter->GetAngle();
	//static_cast<AWavesCharacter>(AWavesCharacter)
	
	//APlayerController* PlayerController = Cast<APlayerController>(plGetController());
	//PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	//vHeading = FVector(MousePosition.X - (ViewportSize.X / 2), MousePosition.Y - (ViewportSize.Y / 2), 0.f);
	//vHeading = FVector(1.f, 0.f, 0.f);
	
	//UE_LOG(LogTemp, Warning, TEXT("TEST: %f %f"), vHeading.X, vHeading.Y);
	
	this->SetActorLocation(this->GetActorLocation() + (vHeading * fSpeed));
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