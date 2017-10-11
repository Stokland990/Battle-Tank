// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
		private:

	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//start to moving the barrel so that the shot would hit where crosshair intersects the world
	void AimTowardsCrosshair();

	//return an OUT parametr, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 100000;



	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

};
