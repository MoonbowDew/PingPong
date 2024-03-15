// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PPPlayerController.h"

#include "Players/PPPlayer.h"

// Called to bind functionality to input

void APPPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APPPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!MovementDirection.IsZero())
	{
		if (APPPlayer* PPPlayer = Cast<APPPlayer>(GetPawn()))
		{
			FVector NewLocation = GetPawn()->GetActorLocation() + (MovementDirection * PPPlayer->GetActorRightVector() * DeltaTime * MovementSpeed);
			if (NewLocation.Y < 2200 && NewLocation.Y > -2200)
			{
				PPPlayer->SetActorLocation(NewLocation);
			}
		}
	}
}


void APPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("Move", this, &APPPlayerController::Move);
}



void APPPlayerController::Move(float movementDelta) {
	ServerMove(movementDelta);
}
bool APPPlayerController::ServerMove_Validate(float movementDelta) {
	return true;
}
void APPPlayerController::ServerMove_Implementation(float movementDelta) {
	if (GetLocalRole() == ROLE_Authority) {
		BroadcastMove(movementDelta);
	}
}
void APPPlayerController::BroadcastMove_Implementation(float movementDelta) {
	MovementDirection.Y = FMath::Clamp(movementDelta, -1.0f, 1.0f);
	if (APPPlayer* PPPlayer = Cast<APPPlayer>(GetPawn()))
	{
		PPPlayer->AddMovementInput(PPPlayer->GetActorRightVector(), movementDelta, false);
	}
	
}