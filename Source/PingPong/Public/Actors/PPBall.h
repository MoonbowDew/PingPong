// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPBall.generated.h"

class APPPlayer;
class APPWall;

UCLASS()
class PINGPONG_API APPBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPBall();

	UFUNCTION()
	void BallHit(AActor* OverlappedActor, AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* PlainMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Wall")
	APPWall* Wall;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	APPPlayer* Player;

	UPROPERTY(replicated)
	FVector Velocity;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move(float movementDelta);
	void MoveBall(float movementDelta);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerMoveBall(float scale);
	void ServerMoveBall_Implementation(float scale);
	bool ServerMoveBall_Validate(float scale);

	UFUNCTION(NetMulticast, Reliable)
	void BroadcastMoveBall(float scale);
	void BroadcastMoveBall_Implementation(float scale);

private:
	FVector MovementDirection = FVector::OneVector;
	float MovementSpeed = 450;



};
