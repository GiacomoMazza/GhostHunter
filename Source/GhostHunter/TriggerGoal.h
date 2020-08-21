// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//Needed for the trigger to work
#include "Engine/TriggerBox.h"
//Needed for array functions
#include "Containers/Array.h"
#include "TriggerGoal.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTHUNTER_API ATriggerGoal : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	ATriggerGoal();

	//UFUNCTION()
		//void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	//Function to detect the end of overlapping
	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	//The new location the trigger will be spawned at
	//UPROPERTY(EditAnywhere, Category = Location)
	//	FVector NewLocation;

	////The new rotation the trigger will be spawned at (implemented if endless runner has curves)
	//UPROPERTY(EditAnywhere, Category = Location)
	//	FQuat NewRotation;

	//Needed to spawn the packages randomly in the environment (Array for position)
	UPROPERTY(EditAnywhere, Category = Location)
		TArray<FVector> LocationArray;

	//Needed to spawn the packages randomly in the environment (Array for rotation)
	UPROPERTY(EditAnywhere, Category = Location)
		TArray<FQuat> RotationArray;

	//Number of packages collected
	int in_Goals = 0;

protected:

	//Used to check if the package's last position would be the same as the new position
	int CheckRandom = 0;

	//bool bl_IsItBegin = true;
};
