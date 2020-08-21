// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTHUNTER_API UBTService_CheckPlayer : public UBTService
{
	GENERATED_BODY()
	
public:
	
	UBTService_CheckPlayer();

	//We need to override this - It receives ticks.
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
