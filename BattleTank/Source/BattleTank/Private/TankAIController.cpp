// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankAIController.h"
#include <string>
#include "Public/TankAimingComponent.h"
#include "Classes/Engine/World.h"



void  ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
		//move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		//aim towards the player
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		//fire if ready
		//ControlledTank->Fire(); //TODO Limit firing rate
	
}




