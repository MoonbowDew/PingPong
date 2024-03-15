// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PPGameModeBase.generated.h"

class APPGameStateBase;
/**
 * 
 */
UCLASS()
class PINGPONG_API APPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	int32 NextPlayerIndex = -1;

public:
	void StartGame();

protected:

	virtual void PostLogin(APlayerController* NewPlayer);

};
