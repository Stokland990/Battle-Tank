// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankAIController.h"
#include "Public/Tank.h"
#include <string>
#include "Classes/Engine/World.h"



void  ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		//TODO move towards the player

		//aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		//fire if ready
		ControlledTank->Fire(); //TODO Limit firing rate
	}
}




