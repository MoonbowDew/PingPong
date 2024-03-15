// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PPPlayer.generated.h"

class APPBall;
DECLARE_EVENT(APPPlayer, FMove);

UCLASS()
class PINGPONG_API APPPlayer : public APawn
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionMesh = nullptr;


public:
	// Sets default values for this pawn's properties
	APPPlayer();

	// Update camera ZS movements over network
	//void Move(float scale);

	FORCEINLINE TSubclassOf <APPBall> GetBall() const { return Ball; }

	UFUNCTION()
	void OnSpawnBall();

	UFUNCTION()
	void OnRep_Ball();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* PlainMesh;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;


	//void Move(float movementDelta);

	//UFUNCTION()
	//void HitObject(AActor* OverlappedActor, AActor* OtherActor);

protected:

	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere)
	//APPBall* Ball;
	TSubclassOf <APPBall> Ball;

private:



};
