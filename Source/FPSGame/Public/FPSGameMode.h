// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

/**
 * GameMode只存在于服务器上
 */
UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFPSGameMode();

	void CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category="GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn, bool bMissionSuccess);

protected:
	/**TSubclassof解释参考https://gameinstitute.qq.com/community/detail/121836
	TSubclassof模板提供了一个安全的虚幻类，他的好处有一下几个：
	1.方便关卡设计师编辑
	  官方推荐的的定义方式是
      // type of damage 
	  UPROPERTY(EditDefaultsOnly, Category = Damage)
      TSubclassOf<UDamageType> DamageType;
	  官方推荐的这样方式的好处是在编辑器中，会给出游戏中所有的伤害类型，我们直接选择就可以，如果是UClass类，则会所有的类都会满足！降低了效率。
	2.在运行时，类型转换的安全
	*/
	UPROPERTY(EditDefaultsOnly, Category ="Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;
};



