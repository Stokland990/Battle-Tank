// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include <string>
#include "Public/TankAimingComponent.h"
#include "Classes/GameFramework/PlayerController.h"
#include "Classes/Engine/World.h"
#include "Classes/GameFramework/Controller.h"



 
void  ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Aim
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation; //Out Parametr
	if (GetSightRayHitLocation(HitLocation)) //Has side-effect, is going to line trace
	{
		
		AimingComponent->AimAt(HitLocation);
	}
}

//Get world location through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	//position of the crosshair in the world direction 
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//line trace along that Look direction, and see what we hit
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return true;
}

	bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
	{
		FVector CameraWorldLocation; //To be discarded
		return DeprojectScreenPositionToWorld(
			ScreenLocation.X,
			ScreenLocation.Y,
			CameraWorldLocation,
			LookDirection);
	}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	if
		(
		GetWorld()->LineTraceSingleByChannel
			(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
			)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);
	return false; //Line trace didn't sucseed
}
