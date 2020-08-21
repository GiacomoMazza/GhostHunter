// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GhostHunterCharacter.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/PrimitiveComponent.h"
#include "Components/CapsuleComponent.h"

#include "Math/Vector.h"

#include "EnemyCharacter.generated.h"

UCLASS()
class GHOSTHUNTER_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	//Reference to behaviourtree
	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree *BotBehaviour;

	//Member to control speed
	UPROPERTY(EditAnywhere, Category = Behavior)
		float fl_Speed;

	//Member to control time to wait before reactivating movement
	UPROPERTY(EditAnywhere, Category = Behavior)
		float fl_TimeToWait;

	//The actor to spawn (Should be a red light) 
	UPROPERTY(EditAnywhere, Category = Behavior)
		TSubclassOf<AActor> ActorToSpawn;

	//The actor to spawn (Should be a green light) 
	UPROPERTY(EditAnywhere, Category = Behavior)
		TSubclassOf<AActor> ActorToSpawnGreen;

	//UPROPERTY(EditAnywhere, Category = Behavior)
	//class UBTTask_MoveToPlayer *PlayerTask;

	//UPROPERTY(EditAnywhere, Category = Behavior)
	//class AGhostHunterCharacter *Enemy;

	//Pointer to CapsuleComponent
	UPROPERTY(VisibleAnywhere, Category = Behavior)
		class UCapsuleComponent *MyCapsule;

	//UPROPERTY(VisibleAnywhere, Category = Behavior)
	//	class UCapsuleComponent *MyCapsule;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Function to spawn the object - red light
	UFUNCTION()
	void SpawnObject(FVector Location, FRotator Rotation);

	//Function to spawn the object - green light
	UFUNCTION()
		void SpawnObjectGreen(FVector Location, FRotator Rotation);

	//Vector that stores the initial player's spawn location
	FVector SpawnLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Function that gets called every so often
	void RepeatingFunction();

	//Function to re-activate the speed or to nullify it
	void ReactivateSpeed();

	//Function that gets activate when a Hit event is generated
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	//Bool to either stop the AI or not
	bool bl_AmIStopped = true;

	//Member to hide Time functions
	FTimerHandle MyTimerHandle;

};
