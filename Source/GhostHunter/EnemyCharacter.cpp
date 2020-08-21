// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "GhostHunter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "GhostHunterCharacter.h"

#include "TimerManager.h"

#include "Engine/World.h"

#include "BTTask_MoveToPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyAI.h"

#include "Engine/Engine.h"

#include "GameFramework/PlayerController.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

//Function that activates after a hit event has been generated
void AEnemyCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString(OtherActor->GetName()));

	//If the other collision object is the player, spawn a green light and restart the player's position
	if (OtherActor->GetName() == "ThirdPersonCharacter_2")
	{
		SpawnObjectGreen(GetActorLocation(), GetActorRotation());
		//GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(SpawnLocation, false);
		OtherActor->SetActorLocation(SpawnLocation, false);
	}
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//On begin, set the player's speed
	GetCharacterMovement()->MaxWalkSpeed = fl_Speed;

	//Set the spawning location so once the player is hit by the AI, we can use this position to respawn it here
	SpawnLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	//MyCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MYCAPSULECOMPONENT"));
	//MyCapsule->BodyInstance.SetCollisionProfileName(TEXT("Hey"));
	//MyCapsule->InitCapsuleSize(36.0f, 90.0f);
	//RootComponent = MyCapsule;

	//Get the capsule
	MyCapsule = GetCapsuleComponent();

	//If the capsule pointer isn't null, "initialise" the OnHit function
	if (MyCapsule != nullptr)
	{
		MyCapsule->OnComponentHit.AddDynamic(this, &AEnemyCharacter::OnHit);
	}

	//Once we push play let's repeat the function every fl_TimeToWait seconds - Start after 5 seconds the game has started
	GetWorldTimerManager().SetTimer(MyTimerHandle, this, &AEnemyCharacter::RepeatingFunction, fl_TimeToWait, true, 15.0f);
}

//Function to spawn the object
void AEnemyCharacter::SpawnObject(FVector Location, FRotator Rotation)
{
	FActorSpawnParameters SpawnParams;
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, Rotation, SpawnParams);
}

//Function to spawn the object
void AEnemyCharacter::SpawnObjectGreen(FVector Location, FRotator Rotation)
{
	FActorSpawnParameters SpawnParams;
	AActor* SpawnedActorGreen = GetWorld()->SpawnActor<AActor>(ActorToSpawnGreen, Location, Rotation, SpawnParams);
}

//Function that gets called every fl_TimeTOWait seconds. Switches the bools to let the character move or not, and then
//calls a function to set the speed according to the bool being false or not
void AEnemyCharacter::RepeatingFunction() {
	bl_AmIStopped = !bl_AmIStopped;
	ReactivateSpeed();
}

//Function that gets called from RepeatingFunction, it sets the AI's speed depedning on the bool being true or false
void AEnemyCharacter::ReactivateSpeed() {
	if (bl_AmIStopped)
	{
		GetCharacterMovement()->MaxWalkSpeed = fl_Speed;
	}

	else if (!bl_AmIStopped) {
		GetCharacterMovement()->MaxWalkSpeed = 0;
		SpawnObject(GetActorLocation(), GetActorRotation());
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get task from this and then reference ubbtask to check the boolean
	//if (PlayerTask != nullptr)
	//{
	//	if (PlayerTask->bl_HasReachedDestination) {

	//	}
	//}

	//COLLISION
	//if (Enemy != nullptr) {
	//	if (Enemy->GetActorLocation() == GetActorLocation()) {
	//		SpawnObjectGreen(GetActorLocation(), GetActorRotation());
	//	}
	//}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

