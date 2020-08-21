// Fill out your copyright notice in the Description page of Project Settings.

//Needed to check player

#include "BTService_CheckPlayer.h"
#include "GhostHunter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "GhostHunterCharacter.h"
#include "EnemyCharacter.h"
#include "EnemyAI.h"


UBTService_CheckPlayer::UBTService_CheckPlayer() {
	//This needs to be an instance since we need to put it on different AIs.
	bCreateNodeInstance = true;
}

void UBTService_CheckPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	//Cast to controller - Get AI controller Cast
	AEnemyAI *EnemyPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	//Check if it's there
	if (EnemyPC) {
		//Is the player in the world?
		AGhostHunterCharacter *Enemy = Cast<AGhostHunterCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		
		//If the enemy exists, get blackboard component.
		if (Enemy) {
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyPC->EnemyKeyID, Enemy);

		}
	}
}