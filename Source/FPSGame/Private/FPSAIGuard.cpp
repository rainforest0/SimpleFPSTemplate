// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnHearNoise);
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeePawn);

	OriginRotator = GetActorRotation();
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSAIGuard::OnSeePawn(APawn* SeenPawn)
{
	if (nullptr == SeenPawn)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("I See You Name::::%s"), *SeenPawn->GetName());
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);

	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->CompleteMission(SeenPawn, false);
	}
}

void AFPSAIGuard::OnHearNoise(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (nullptr == NoiseInstigator)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("I Hear You Name::::%s"), *NoiseInstigator->GetName());
	DrawDebugSphere(GetWorld(), NoiseInstigator->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 10.0f);

	FVector Direct = Location - GetActorLocation();
	Direct.Normalize();

	//ֻ��Ӱ��Yaw������ת�����ı仯������Ӱ����ת���Pitch������ת������Roll����бת��������������AI�����������ŵ�����
	FRotator NewRotator = FRotationMatrix::MakeFromX(Direct).Rotator();
	NewRotator.Pitch = 0.0f;
	NewRotator.Roll = 0.0f;
	SetActorRotation(NewRotator);

	//��ʵֻҪ������TimerHandle_ResetRatation��SetTimer�л����InternalClearTimer
	//����ֻҪʹ��ͬһ��TimerHandle_ResetRatation��������ҪClearTimer
	//GetWorldTimerManager().ClearTimer(TimerHandle_ResetRatation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetRatation, this, &AFPSAIGuard::ResetRatationTimerCallback, 3.0f, false);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSAIGuard::ResetRatationTimerCallback()
{
	SetActorRotation(OriginRotator);
}


