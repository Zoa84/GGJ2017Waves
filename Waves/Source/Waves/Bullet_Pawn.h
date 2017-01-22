// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Bullet_Pawn.generated.h"

UCLASS()
class WAVES_API ABullet_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABullet_Pawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Return mesh
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return BulletMesh; }

	void SetHeading(FVector f);

	void SetWeapons(bool b1, bool b2, bool b3);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BulletMesh;

	float fSpeed;
	int iType;
	FVector vHeading;
	bool bWeapon1;
	bool bWeapon2;
	bool bWeapon3;

	ConstructorHelpers::FObjectFinder <UMaterialInterface>* Material_Red;
	ConstructorHelpers::FObjectFinder <UMaterialInterface>* Material_Green;
	ConstructorHelpers::FObjectFinder <UMaterialInterface>* Material_Blue;
};
