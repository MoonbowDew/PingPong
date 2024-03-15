// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/PPPlayer.h"

#include "Actors/PPBall.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APPPlayer::APPPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	PlainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	UStaticMesh* cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	PlainMesh->SetStaticMesh(cubeMesh);
	PlainMesh->SetRelativeScale3D(FVector(0.2f, 4.0f, 1.3f));
	PlainMesh->SetCollisionProfileName("NoCollision");

	SetRootComponent(PlainMesh);

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetCollisionProfileName("OverlapAllDynamic");

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 700.0f; // The camera follows at this distance behind the character	
	CameraBoom->SocketOffset.Z = 600.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetRelativeRotation(UKismetMathLibrary::MakeRotator(0.0f, -30.0f, 0.0f));
	
	static ConstructorHelpers::FClassFinder<APPBall> BallBPClass(TEXT("/Game/Blueprints/BP_PPBall"));
	if (BallBPClass.Class != nullptr)
	{
		Ball = BallBPClass.Class;
	}

}

// Called when the game starts or when spawned
void APPPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void APPPlayer::OnSpawnBall()
{
	//Server-specific functionality
	if (GetLocalRole() == ROLE_Authority)
	{
		FVector Location(490.0f, 20.0f, 70.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;

		GetWorld()->SpawnActor<APPBall>(Ball, Location, Rotation, SpawnInfo);
	}

}

void APPPlayer::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APPPlayer, Ball);
}



void APPPlayer::OnRep_Ball()
{
	OnSpawnBall();
}