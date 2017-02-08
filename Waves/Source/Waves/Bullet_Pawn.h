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

	FString getWeaponType();

	UFUNCTION()
		void OnOverlap(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnHit(class UPrimitiveComponent* HitComp, class AActor* Actor, class UPrimitiveComponent* Other, FVector Impulse, const FHitResult & HitResult);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BulletMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent * boxComponent;

	float fSpeed;
	FVector vHeading;
	
	//The type of bullet (Red, Greeb, Blue)
	FString sType;

	ConstructorHelpers::FObjectFinder <UMaterialInterface>* Material_Red;
	ConstructorHelpers::FObjectFinder <UMaterialInterface>* Material_Green;
	ConstructorHelpers::FObjectFinder <UMaterialInterface>* Material_Blue;
};
