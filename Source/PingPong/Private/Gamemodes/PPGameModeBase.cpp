// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/PPGameModeBase.h"

#include "Actors/PPBall.h"
#include "Kismet/GameplayStatics.h"
#include "Players/PPPlayer.h"
#include "GameFramework/PlayerStart.h"

AActor* APPGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	//Super::ChoosePlayerStart(Player);

	NextPlayerIndex = NextPlayerIndex + 1;

	TArray<AActor*> FoundPlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundPlayerStarts);
	return FoundPlayerStarts[NextPlayerIndex];
}

void APPGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if(GetNumPlayers() < 2)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("The number of players is less than 2; can't start the game")));
	if (GetNumPlayers() >= 2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("The game session successfully started")));
		StartGame();
	}

}

void APPGameModeBase::StartGame()
{
	Cast<APPPlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn())->OnRep_Ball();
}