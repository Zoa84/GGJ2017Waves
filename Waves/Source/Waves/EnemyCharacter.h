// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class WAVES_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	bool isDead();
private:
	//! Calculate heading for moving towards specified position
	FVector calcHeading(FVector target);
	
	//! Speed of actor (as a multiplier)
	UPROPERTY(EditAnywhere, Category = "Enemy")
	float fSpeed;
	UPROPERTY(EditAnywhere, Category = "Enemy")
	FString sType;
	UPROPERTY(EditAnywhere, Category = "Enemy")
	int iHealth;

	bool bDead;

	void takeDamage(int damage);

	UCapsuleComponent* capsuleComp;

	ConstructorHelpers::FObjectFinder <UMaterialInterface>* Material_Red;
	ConstructorHelpers::FObjectFinder <UMaterialInterface>* Material_Green;
	ConstructorHelpers::FObjectFinder <UMaterialInterface>* Material_Blue;

	UFUNCTION()
	virtual void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
