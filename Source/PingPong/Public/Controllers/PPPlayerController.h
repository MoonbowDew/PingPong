// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "PPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APPPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	//UFUNCTION()
	void Move(float movementDelta);

	/** Property replication */
	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void SetupInputComponent() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerMove(float scale);
	void ServerMove_Implementation(float scale);
	bool ServerMove_Validate(float scale);

	UFUNCTION(NetMulticast, Reliable)
	void BroadcastMove(float scale);
	void BroadcastMove_Implementation(float scale);

private:


protected:

	//UPROPERTY(ReplicatedUsing = OnRep_Move)
	FVector MovementDirection = FVector::ZeroVector;

	/*
	UFUNCTION()
	void OnRep_Move();*/

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 900.0f;

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
