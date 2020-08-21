// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameManager.h"

//Needed for recurrent functions over time functions
#include "TimerManager.h"

//Needed to reference the player character
#include "GhostHunterCharacter.h"

//Needed to access the player's movement components
#include "GameFramework/CharacterMovementComponent.h"

//Needed to access the Character functions
#include "GameFramework/Character.h"

// Sets default values
AMyGameManager::AMyGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

///Cooldown function called after the character jumps. Calls Enable Jump to enable the jump.
void AMyGameManager::StartJumpTimer() {
	GetWorldTimerManager().SetTimer(JumpTimeHandler, this, &AMyGameManager::EnableJump, fl_CharWaitJump, false, 15.0f);
}

// Called when the game starts or when spawned
void AMyGameManager::BeginPlay()
{
	Super::BeginPlay();

	//GetWorldTimerManager().SetTimer(JumpTimeHandler, this, &AMyGameManager::EnableJump, fl_CharWaitJump, true, 15.0f);
}

///Enable a bool that enables the character's jump.
void AMyGameManager::EnableJump() {	
	bl_CanCharJump = true;
}

// Called every frame
void AMyGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Increments elapsed time.
	fl_TimeElapsed += DeltaTime;

	//Addresses the player's CharacterMovement Component
	UCharacterMovementComponent* CharMovement = MyPlayer->FindComponentByClass<UCharacterMovementComponent>();
	
	//If the pointer is not null
	if (CharMovement != nullptr)
	{
		//If the character is not falling
		if (!CharMovement->IsFalling()) {

			//If the character is not jumping because of this it means that it just jumped, so set its Jump speed to 0
			if (!bl_CanCharJump)
			{
				CharMovement->JumpZVelocity = 0.0f;
			}

			//Otherwise, start the cooldown for the jump and set its velocity to 600
			else if (bl_CanCharJump) {
				CharMovement->JumpZVelocity = 600;
				StartJumpTimer();
			}
		}

		//Otherwise this means it is falling, meaning it just jumped, so set this to false
		else if (CharMovement->IsFalling()) {
			bl_CanCharJump = false;
		}
	}
}

