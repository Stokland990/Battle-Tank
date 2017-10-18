// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be the last include

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:


	
	UFUNCTION(BlueprintImplementableEvent, Category = SetUp)
		void FoundAimingComponent(UTankAimingComponent* AimingCompRef);
	
private:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//start to moving the barrel so that the shot would hit where crosshair intersects the world
	void AimTowardsCrosshair();

	//return an OUT parametr, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 100000;



	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

};
