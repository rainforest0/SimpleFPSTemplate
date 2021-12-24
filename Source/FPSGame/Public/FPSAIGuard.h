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

	//1.最早用的是PawnSensingComponent，但是该组件现在目前已被Unreal官方弃用（不推荐但仍保留），相对于AIPerceptionComponent来说更简单，用起来更方便；
	//2.官方推荐使用的AI感知解决方案为AIPerceptionComponent,官方解释为AIPerceptionComponent在灵活性以及性能开销方面效果更佳，比如在视觉感知方面对每帧的trace及查询增加了上限次数等优化处理。
	// 该组件比UPawnSensingComponent实现起来麻烦，不过功能比较多．例如在做队伍之间的信息通知；
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
