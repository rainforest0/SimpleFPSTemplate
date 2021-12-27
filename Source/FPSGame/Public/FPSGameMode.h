// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

/**
 * GameModeֻ�����ڷ�������
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
	/**TSubclassof���Ͳο�https://gameinstitute.qq.com/community/detail/121836
	TSubclassofģ���ṩ��һ����ȫ������࣬���ĺô���һ�¼�����
	1.����ؿ����ʦ�༭
	  �ٷ��Ƽ��ĵĶ��巽ʽ��
      // type of damage 
	  UPROPERTY(EditDefaultsOnly, Category = Damage)
      TSubclassOf<UDamageType> DamageType;
	  �ٷ��Ƽ���������ʽ�ĺô����ڱ༭���У��������Ϸ�����е��˺����ͣ�����ֱ��ѡ��Ϳ��ԣ������UClass�࣬������е��඼�����㣡������Ч�ʡ�
	2.������ʱ������ת���İ�ȫ
	*/
	UPROPERTY(EditDefaultsOnly, Category ="Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;
};



