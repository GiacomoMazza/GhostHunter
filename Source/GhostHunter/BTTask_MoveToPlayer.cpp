// Fill out your copyright notice in the Description page of Project Settings.



#include "BTTask_MoveToPlayer.h"
#include "GhostHunter.h"

//Needed for BehaviourTree functions
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

//Needed to reference the EnemyCharacter
#include "EnemyCharacter.h"
//Needed to reference the EnemyAI
#include "EnemyAI.h"
//Needed to reference the player
#include "GhostHunterCharacter.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	//Get player controller
	AEnemyAI *CharPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	//Get Enemy object using the ID we stored in the Blackboard.
	AGhostHunterCharacter *Enemy = Cast<AGhostHunterCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPC->EnemyKeyID));

	//If the enemy (Player) exists, move toward it and return succeeded, otherwise failed.
	if (Enemy) {
		CharPC->MoveToActor(Enemy, 0.f, true, true, true, 0, true);
		return EBTNodeResult::Succeeded;
	}

	else {
		return EBTNodeResult::Failed;
	}

	//if (CharPC->GetMoveStatus() == EPathFollowingStatus::Idle) {
	//	bl_HasReachedDestination = true;
	//}

	//else if (CharPC->GetMoveStatus() != EPathFollowingStatus::Idle) {
	//	bl_HasReachedDestination = false;
	//}
}
