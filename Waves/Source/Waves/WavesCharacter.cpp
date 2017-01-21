// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Waves.h"
#include "WavesCharacter.h"

#define TO_RADIANS	3.14159 / 180
#define TO_DEGREES	180 / 3.14159

AWavesCharacter::AWavesCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)


	//Try to show mouse
	//PlayerController->bShowMouseCursor = true;
	//PlayerController->bEnableClickEvents = true;
	//PlayerController->bEnableMouseOverEvents = true;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AWavesCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	//InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAxis("MoveRight", this, &AWavesCharacter::MoveRight);

	InputComponent->BindTouch(IE_Pressed, this, &AWavesCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AWavesCharacter::TouchStopped);
}

void AWavesCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);

	//Look at mouse position

	//Viewport Size
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	//Viewport Center!            
	const FVector2D  ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);

	//Mouse positions
	float x;
	float y;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->GetMousePosition(x, y);

	FVector2D MousePosition(x, y);

	if ((MousePosition.X < 0) || (MousePosition.Y < 0) || (MousePosition.X > ViewportSize.X) || (MousePosition.Y > ViewportSize.Y))
	{

	}
	else
	{

		FVector2D LocalPos(MousePosition.X - ViewportCenter.X, MousePosition.Y - ViewportCenter.Y);

		//UE_LOG(LogTemp, Warning, TEXT("X: %f Y: %f"), ViewportSize.X, ViewportSize.Y);
		//UE_LOG(LogTemp, Warning, TEXT("X: %f Y: %f"), LocalPos.X, LocalPos.Y);

		FVector testing = FVector(LocalPos, 0.f);
		float test = (testing.HeadingAngle() * TO_DEGREES) + 180.f;
		UE_LOG(LogTemp, Warning, TEXT("Angle: %f"), test);

		FRotator kill = FRotator(0.f, test + 90.f, 0.f);

		this->SetActorRotation(kill);
	}
}

void AWavesCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AWavesCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

