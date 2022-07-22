// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WarPlane.generated.h"

class UStaticMeshComponent;

UCLASS()
class JET_API AWarPlane : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWarPlane();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;
    UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Fuselage;
	UPROPERTY(EditDefaultsOnly)
    UStaticMeshComponent* Glass;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RudderL;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RudderR;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ElevatorL;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ElevatorR;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* AileronL;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* AileronR;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* flapsL;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* flapsR;


	void EngineBoostInput(float Val);

	void SlowDownInput(float Val);

	void RightRotationInput(float Val);

	void EngineBoostTimer();

	void EngineOverHeat();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(Category = Pitch, EditAnywhere)
	float MaxSpeed;

	/** Min forward speed */
	UPROPERTY(Category=Yaw, EditAnywhere)
	float MinSpeed;

	/** Current forward speed */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	float CurrentForwardSpeed;

	/** Current yaw speed */
	float CurrentYawSpeed;

	/** Current pitch speed */
	float CurrentPitchSpeed;

	/** Current roll speed */
	float CurrentRollSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	float EngineBoostTime;
	
	bool EngineControl;
	bool OverHeating;

	float ChangeValue;

	FTimerHandle Timer;
	FTimerHandle Timer2;
	
};
