// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnHearNoise);
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeePawn);

	OriginRotator = GetActorRotation();

	GuardState = EAIState::Idle;
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

	SetGuardState(EAIState::Alerted);
}

void AFPSAIGuard::OnHearNoise(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (nullptr == NoiseInstigator)
	{
		return;
	}

	if (GuardState == EAIState::Alerted)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("I Hear You Name::::%s"), *NoiseInstigator->GetName());
	DrawDebugSphere(GetWorld(), NoiseInstigator->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 10.0f);

	FVector Direct = Location - GetActorLocation();
	Direct.Normalize();

	//只需影响Yaw（左右转动）的变化，不会影响旋转体的Pitch（上下转动）和Roll（倾斜转动），否则会出现AI整个体型仰着的情形
	FRotator NewRotator = FRotationMatrix::MakeFromX(Direct).Rotator();
	NewRotator.Pitch = 0.0f;
	NewRotator.Roll = 0.0f;
	SetActorRotation(NewRotator);

	//其实只要保存了TimerHandle_ResetRatation，SetTimer中会调用InternalClearTimer
	//所以只要使用同一个TimerHandle_ResetRatation，并不需要ClearTimer
	//GetWorldTimerManager().ClearTimer(TimerHandle_ResetRatation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetRatation, this, &AFPSAIGuard::ResetRatationTimerCallback, 3.0f, false);

	SetGuardState(EAIState::Suspicious);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSAIGuard::ResetRatationTimerCallback()
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}

	SetActorRotation(OriginRotator);

	SetGuardState(EAIState::Idle);
}

void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
	{
		return;
	}

	GuardState = NewState;
	OnRep_GuardState();
}

void AFPSAIGuard::OnRep_GuardState()
{
	OnStateChanged(GuardState);
}

void AFPSAIGuard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSAIGuard, GuardState);
}
