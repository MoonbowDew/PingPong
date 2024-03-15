// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PPWall.h"

#include "Components/BoxComponent.h"

// Sets default values
APPWall::APPWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	UStaticMesh* cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	PlainMesh->SetStaticMesh(cubeMesh);
	PlainMesh->SetRelativeScale3D(FVector(70.0f, 0.5f, 5.0f));
	PlainMesh->SetCollisionProfileName("NoCollision");

	SetRootComponent(PlainMesh);

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetRelativeScale3D(FVector(1.0f, 1.0f,1.0f));
	CollisionMesh->SetCollisionProfileName("OverlapAllDynamic");

}

// Called when the game starts or when spawned
void APPWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APPWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

