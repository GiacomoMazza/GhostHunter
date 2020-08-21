// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "EnemyAI.generated.h"
/**
 * 
 */
UCLASS()//CONTROLLER CLASS
class GHOSTHUNTER_API AEnemyAI : public AAIController
{
	GENERATED_BODY()

		//Add blackboard component
	UPROPERTY(transient)
	class UBlackboardComponent * BlackboardComp;

	//Add behaviourtree component
	UPROPERTY(transient)
	class UBehaviorTreeComponent * BehaviorComp;

public:
	//Constructor
	AEnemyAI();

	//Void to be called to control the pawn
	virtual void OnPossess(APawn *InPawn) override;

	//Add key IDs - Needed for the blackboard key, which is the target.
	uint8 EnemyKeyID;
};
