// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Waves.h"
#include "WavesCharacter.h"

#define TO_RADIANS	3.14159 / 180
#define TO_DEGREES	180 / 3.14159

#define STATE_MOVING	0
#define STATE_BATTLE	1
#define STATE_DEATH		2

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



	iState = STATE_MOVING;
	bWeapon1 = false;
	bWeapon2 = false;
	bWeapon3 = false;
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
	InputComponent->BindAction("Switch", IE_Pressed, this, &AWavesCharacter::Switch);
	
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AWavesCharacter::Shoot);
	//InputComponent->BindAction("SubShoot", IE_Pressed, this, &AWavesCharacter::);
	InputComponent->BindAction("Weapon1", IE_Pressed, this, &AWavesCharacter::Weapon1On);
	InputComponent->BindAction("Weapon2", IE_Pressed, this, &AWavesCharacter::Weapon2On);
	InputComponent->BindAction("Weapon3", IE_Pressed, this, &AWavesCharacter::Weapon3On);
	InputComponent->BindAction("Weapon1", IE_Released, this, &AWavesCharacter::Weapon1Off);
	InputComponent->BindAction("Weapon2", IE_Released, this, &AWavesCharacter::Weapon2Off);
	InputComponent->BindAction("Weapon3", IE_Released, this, &AWavesCharacter::Weapon3Off);
}

void AWavesCharacter::MoveRight(float Value)
{
	if (iState == STATE_MOVING)
	{
		//add movement in that direction
		AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
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

// Called every frame
void AWavesCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Tick!"));

	if (iState == STATE_MOVING)
	{
		
	}
	else if (iState == STATE_BATTLE)
	{
		LookAt();
	}
	else if (iState == STATE_DEATH)
	{

	}
}

//Look at mouse position
void AWavesCharacter::LookAt()
{
	//Set Viewport Size
	ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	//Mouse positions
	FVector2D MousePosition;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

	if ((MousePosition.X < 0) || (MousePosition.Y < 0) || (MousePosition.X > ViewportSize.X) || (MousePosition.Y > ViewportSize.Y))
	{
		/** If outside bounds of screen, do not update player rotation */
	}
	else
	{
		FVector LocalPos = FVector(MousePosition.X - (ViewportSize.X / 2), MousePosition.Y - (ViewportSize.Y / 2), 0.f);
		fAngle = (LocalPos.HeadingAngle() * TO_DEGREES) + 270.f;
		this->SetActorRotation(FRotator(0.f, fAngle, 0.f));
	}
}

void AWavesCharacter::Switch()
{
	iState++;
	if (iState > STATE_DEATH)
	{
		iState = STATE_MOVING;
	}
	UE_LOG(LogTemp, Warning, TEXT("State: %i"), iState);
}

void AWavesCharacter::Shoot()
{
	if (iState == STATE_BATTLE)
	{
		if (bWeapon1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Weapon 1"));
		}
		else if (bWeapon2)
		{
			UE_LOG(LogTemp, Warning, TEXT("Weapon 2"));
		}
		else if (bWeapon3)
		{
			UE_LOG(LogTemp, Warning, TEXT("Weapon 3"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Weapon"));
		}
		//Shoot a projectile
		//Get a projectile, and pass the angle of the player
		//So the projectile can shoot in that angle
		//Also pass the current weapon selected
		//Then reset weapon states

		//Later on, can mix multiple weapons
	}
}