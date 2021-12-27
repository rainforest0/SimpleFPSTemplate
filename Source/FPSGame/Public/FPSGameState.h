// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

/**
 * GameState存在于所有服务器和客户端上，可自由复制使所有计算机保持最新状态
 */
UCLASS()
class FPSGAME_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnMissionCompleted(APawn* InstigatorPawn, bool bMissionSuccess);
	
};
