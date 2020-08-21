// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAI.h"
#include "GhostHunter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"

AEnemyAI::AEnemyAI() {
	//Initialise Blackboard component
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	//Initialise BehaviourTree component
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComp"));
}

void AEnemyAI::OnPossess(APawn *InPawn) {
	
	//This class is assigned to the pawn via Blueprint.
	Super::OnPossess(InPawn);

	//Gets our character
	AEnemyCharacter *Char = Cast<AEnemyCharacter>(InPawn);

	//If these are not null
	if(Char && Char->BotBehaviour) {
		
		//Initialise Blackboard
		BlackboardComp->InitializeBlackboard(*Char->BotBehaviour->BlackboardAsset);

		//Assign enemy Key ID to a particular object (Target defined in Blueprint Blackboard) from our blackboard
		EnemyKeyID = BlackboardComp->GetKeyID("Target");

		//Start the behaviour tree
		BehaviorComp->StartTree(*Char->BotBehaviour);
	}
}
