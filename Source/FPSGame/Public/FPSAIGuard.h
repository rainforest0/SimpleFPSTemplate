// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//1.�����õ���PawnSensingComponent�����Ǹ��������Ŀǰ�ѱ�Unreal�ٷ����ã����Ƽ����Ա������������AIPerceptionComponent��˵���򵥣������������㣻
	//2.�ٷ��Ƽ�ʹ�õ�AI��֪�������ΪAIPerceptionComponent,�ٷ�����ΪAIPerceptionComponent��������Լ����ܿ�������Ч�����ѣ��������Ӿ���֪�����ÿ֡��trace����ѯ���������޴������Ż�����
	// �������UPawnSensingComponentʵ�������鷳���������ܱȽ϶࣮������������֮�����Ϣ֪ͨ��
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnSeePawn(APawn* SeenPawn);

	UFUNCTION()
	void OnHearNoise(APawn* NoiseInstigator, const FVector& Location, float Volume);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
