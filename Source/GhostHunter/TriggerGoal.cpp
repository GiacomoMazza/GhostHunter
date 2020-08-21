// Fill out your copyright notice in the Description page of Project Settings.

//Necessary for debugginh
#include "Engine/Engine.h"
#include "TriggerGoal.h"
//#include "DrawDebugHelpers.h"

//Constructor to "initialise" the function(s)
ATriggerGoal::ATriggerGoal() {
	//OnActorBeginOverlap.AddDynamic(this, &ATriggerGoal::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ATriggerGoal::OnOverlapEnd);
}

void ATriggerGoal::BeginPlay() {
	Super::BeginPlay();

	//Number of packages collected. Starts with 0
	in_Goals = 0;

	//Converts in_Goals(int) to string
	FString st_Objectives = FString::FromInt(in_Goals);
	//Debugs the number of package collected at the start of the game, setting a goal for the player
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString(st_Objectives + "/20 objectives captured!"));
	
	//This works only in the editor, which is fine, but consider adding a mesh before distributing it.
	//DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Green, true, -1, 0, 5);
}


//void ATriggerGoal::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) {

	//if (!bl_IsItBegin)
	//{

	//}

	//else if (bl_IsItBegin) bl_IsItBegin = false;
//}

//Function called after the player exits the trigger area
void ATriggerGoal::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor) {
	
	//If there are less than 20 packages being collected
	if (in_Goals < 20)
	{
		//Increment packages collected
		ATriggerGoal::in_Goals++;
		//Converts in_goals(int) to string
		FString st_Objectives = FString::FromInt(in_Goals);
		//Debugs the number of packages collected upon collection
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString(st_Objectives + "/20 objectives captured!"));

		//If there are at least 4 locations where the packages can spawn
		if (LocationArray.Num() >= 4)
		{
			//Generate a random number 
			int MyRandom = FMath::RandRange(0, LocationArray.Num());

			//If the number previously generated and this new one are the same, it means the trigger will spawn in the
			//the same place, so if they are not the same teleport the trigger, otherwise call this function again
			if (MyRandom != CheckRandom)
			{
				SetActorLocationAndRotation(LocationArray[MyRandom], RotationArray[MyRandom], false, 0, ETeleportType::None);
			}

			else if (MyRandom == CheckRandom) {
				OnOverlapEnd(OverlappedActor, OtherActor);
				//if(MyRandom >= 0 && MyRandom <= 1) SetActorLocationAndRotation(LocationArray[MyRandom+1], RotationArray[MyRandom+1], false, 0, ETeleportType::None);
				//else if (MyRandom >= 2 && MyRandom <= 3) SetActorLocationAndRotation(LocationArray[MyRandom-1], RotationArray[MyRandom-1], false, 0, ETeleportType::None);
			}

			//Assign this random number to our variable so we can check if the next random number is the same as the old one
			CheckRandom = MyRandom;
		}
	}

	//If the player has collected more than 20 packages, debug "you won"
	else if (in_Goals >= 20) GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString("You won the game!"));
}