// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//Needed for actor functions
#include "GameFramework/Actor.h"
#include "MyGameManager.generated.h"

UCLASS()
class GHOSTHUNTER_API AMyGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyGameManager();

	//Member for cooldown function
	UPROPERTY(EditAnywhere, Category = PCBehavior)
		float fl_CharWaitJump;

	//Pointer to Character class
	UPROPERTY(EditAnywhere, Category = PCBehavior)
		ACharacter* MyPlayer;

	//Member that allows the player to jump or not
	UPROPERTY(EditAnywhere, Category = PCBehavior)
		bool bl_CanCharJump = true;

	//Neede to handle repeating functions
	FTimerHandle JumpTimeHandler;

	//Member to show time elapsed since the game began
	UPROPERTY(VisibleAnywhere, Category = PCBehavior)
		float fl_TimeElapsed = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Void to enable the player's jump
	void EnableJump();

	//Function to start re-enabling the character's jump
	UFUNCTION()
		void StartJumpTimer();
};
