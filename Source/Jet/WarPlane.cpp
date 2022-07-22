// Fill out your copyright notice in the Description page of Project Settings.


#include "WarPlane.h"

// Sets default values
AWarPlane::AWarPlane()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Fuselage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fuselage"));
	
	Glass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Glass"));
	Glass->SetupAttachment(Fuselage);
	
	RudderL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RudderL"));
	RudderL->AttachTo(Fuselage,TEXT("rudderL"), EAttachLocation::SnapToTargetIncludingScale, true);

	RudderR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RudderR"));
	RudderR->AttachTo(Fuselage,TEXT("rudderR"), EAttachLocation::SnapToTargetIncludingScale, true);

	ElevatorL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElevatorL"));
	ElevatorL->AttachTo(Fuselage,TEXT("elevatorL"), EAttachLocation::SnapToTargetIncludingScale, true);

	ElevatorR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElevatorR"));
	ElevatorR->AttachTo(Fuselage,TEXT("elevatorR"), EAttachLocation::SnapToTargetIncludingScale, true);

	AileronL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AileronL"));
	AileronL->AttachTo(Fuselage,TEXT("aileronL"), EAttachLocation::SnapToTargetIncludingScale, true);

	AileronR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AileronR"));
	AileronR->AttachTo(Fuselage,TEXT("aileronR"), EAttachLocation::SnapToTargetIncludingScale, true);

	flapsL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlapsL"));
	flapsL->AttachTo(Fuselage,TEXT("flapsL"), EAttachLocation::SnapToTargetIncludingScale, true);

	flapsR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlapsR"));
	flapsR->AttachTo(Fuselage,TEXT("flapsR"), EAttachLocation::SnapToTargetIncludingScale, true);

	ChangeValue = 20.f;
	MaxSpeed = 12000.f;
	MinSpeed = 3000.f;
	CurrentForwardSpeed = 5000.f;
	EngineBoostTime = 20.f;

	EngineControl = false;
	OverHeating = false;

	
}

void AWarPlane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("SpeedBoost", this, &AWarPlane::EngineBoostInput);
	PlayerInputComponent->BindAxis("SlowDown", this, &AWarPlane::SlowDownInput);
}


// Called when the game starts or when spawned
void AWarPlane::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWarPlane::Tick(float DeltaTime)
{

	const FVector LocalMove = FVector(CurrentForwardSpeed*DeltaTime, 0.f, 0.f);
	
	AddActorLocalOffset(LocalMove, true);

	// Calculate change in rotation this frame
	FRotator DeltaRotation(0,0,0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaTime;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaTime;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaTime;
	

	// Rotate plane
	AddActorLocalRotation(DeltaRotation);
	Super::Tick(DeltaTime);

}

void AWarPlane::EngineBoostInput(float Val)
{
	if(Val != 0 && EngineBoostTime > 1 && OverHeating == false)
	{
		EngineControl = true;
		if(CurrentForwardSpeed < MaxSpeed)
		{
			CurrentForwardSpeed = CurrentForwardSpeed + (Val*ChangeValue);
		}
		else
		{
			CurrentForwardSpeed = MaxSpeed;
		}
	}
	else
	{
		EngineControl = false;
		if(CurrentForwardSpeed > 5000) CurrentForwardSpeed -= ChangeValue;
	}
}

void AWarPlane::EngineBoostTimer()
{
	if(EngineBoostTime <= 19.9f && EngineControl == false)
	{
		EngineBoostTime = EngineBoostTime + 0.1f;
		
	}
	if(EngineBoostTime >= 1.f && EngineControl)
	{
		EngineBoostTime = EngineBoostTime - 0.1f;
		if(EngineBoostTime <= 1.1)
		{
			OverHeating = true;
			GetWorldTimerManager().SetTimer(Timer2, this, &AWarPlane::EngineOverHeat, 19.f, true);
			
		}
	}
	
	GetWorldTimerManager().SetTimer(Timer, this, &AWarPlane::EngineBoostTimer, 0.1f, true);
}

void AWarPlane::EngineOverHeat()
{
	OverHeating = false;
}

void AWarPlane::SlowDownInput(float Val)
{
	if(Val != 0)
	{
		if(CurrentForwardSpeed > MinSpeed)
		{
			CurrentForwardSpeed = CurrentForwardSpeed - (Val*ChangeValue);
		}
		else
		{
			CurrentForwardSpeed = MinSpeed;
		}
	}
	else
	{
		if(CurrentForwardSpeed < 5000) CurrentForwardSpeed += ChangeValue;
	}
}


