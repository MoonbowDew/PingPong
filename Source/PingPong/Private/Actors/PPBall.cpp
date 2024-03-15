// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PPBall.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actors/PPWall.h"
#include "Net/UnrealNetwork.h"
#include "Players/PPPlayer.h"

// Sets default values
APPBall::APPBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	PlainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	UStaticMesh* cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	PlainMesh->SetStaticMesh(cubeMesh);
	PlainMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	PlainMesh->SetCollisionProfileName("NoCollision");

	SetRootComponent(PlainMesh);

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetCollisionProfileName("OverlapAllDynamic");

	UKismetMathLibrary::RandomBool() ? Velocity.X = -1.0f : Velocity.X = 1.0f;
	UKismetMathLibrary::RandomBool() ? Velocity.Y = -1.0f : Velocity.Y = 1.0f;
	Velocity.Z = 0.0f;

	/*
	static ConstructorHelpers::FClassFinder<APPWall> WallBP(TEXT("/Game/Blueprints/BP_Wall"));
	if(WallBP.Class != nullptr)
	{
		Wall = WallBP.Class;
	}

	static ConstructorHelpers::FClassFinder<APPPlayer> PlayerBP(TEXT("/Game/Blueprints/BP_Player5"));
	if (PlayerBP.Class != nullptr)
	{
		Player = PlayerBP.Class;
	}
	*/
}

void APPBall::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	DOREPLIFETIME(APPBall, Velocity);
}

void APPBall::BallHit(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Cast<APPWall>(OtherActor))
	{
		Velocity.Y = Velocity.Y * -1.0f;
	}

	if (Cast<APPPlayer>(OtherActor))
	{
		Velocity.X = Velocity.X * -1.0f;
	}
}

// Called when the game starts or when spawned
void APPBall::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &APPBall::BallHit);
	
}

// Called every frame
void APPBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);

}

void APPBall::Move(float movementDelta)
{
	FVector NewLocation = GetActorLocation() + (Velocity * movementDelta * MovementSpeed);
	SetActorLocation(NewLocation);
}

void APPBall::MoveBall(float movementDelta) {
	ServerMoveBall(movementDelta);
}
bool APPBall::ServerMoveBall_Validate(float movementDelta) {
	return true;
}
void APPBall::ServerMoveBall_Implementation(float movementDelta) {
	if (GetLocalRole() == ROLE_Authority) {
		BroadcastMoveBall(movementDelta);
	}
}
void APPBall::BroadcastMoveBall_Implementation(float movementDelta) {
	FVector NewLocation = GetActorLocation() + (Velocity * movementDelta * MovementSpeed);
	SetActorLocation(NewLocation);
}