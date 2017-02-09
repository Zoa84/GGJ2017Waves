// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "WavesCharacter.generated.h"

UCLASS(config=Game)
class AWavesCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

private:
	/** Angle the player is facing */
	float fAngle;

	/** Vector of player angle */
	FVector LocalPos;

	/** Viewport Size */
	FVector2D ViewportSize;

	/** Player state (moving, battle and death state */
	int iState;

	/** Weapon states */
	bool bWeapon1;
	bool bWeapon2;
	bool bWeapon3;

	/** Look at mouse position*/
	void LookAt();

	/** Delay till next shot */
	int iDelay;

	UFUNCTION()
		void OnOverlap(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent * boxComponent;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	/** Called to switch states (current space bar) */
	void Switch();

	/** Shooting function */
	void Shoot();

	/** Sub Weapon Shooting function */
	void SubShoot();

	/** Weapon Activation */
	void Weapon1On() { bWeapon1 = true; };
	void Weapon2On() { bWeapon2 = true; };
	void Weapon3On() { bWeapon3 = true; };

	/** Weapon Deactivation */
	void Weapon1Off() { bWeapon1 = false; };
	void Weapon2Off() { bWeapon2 = false; };
	void Weapon3Off() { bWeapon3 = false; };

	//Restart level
	void Reset();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class ABullet_Pawn> Bullet;

	UPROPERTY(EditAnywhere, Category = "Player Character")
	TSubclassOf<class ATextRenderActor> GameOver;

public:
	AWavesCharacter();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

};
