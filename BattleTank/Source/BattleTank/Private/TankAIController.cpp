// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include <string>
#include "Classes/Engine/World.h"



void  ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetPlayerTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No one found you :("))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemie tank found you.  %s"), *ControlledTank->GetName())
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		//TODO move towards the player

		//aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		//fire if ready
	}
}


ATank* ATankAIController::GetPlayerTank() const
{ 
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no player!"))
			return nullptr;
	}
	return Cast<ATank>(PlayerPawn);

}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


