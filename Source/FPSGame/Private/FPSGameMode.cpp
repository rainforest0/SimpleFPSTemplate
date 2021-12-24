// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		//ר�Ž�ֹ����ҿ����������ŵ�Pawn������Ϸ��ɫ������
		InstigatorPawn->DisableInput(nullptr);

		AActor* NewViewTarget = nullptr;

		//�ҳ��������ض������͵�����actor����
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, OutActors);
		if (OutActors.Num())
		{
			NewViewTarget = OutActors[0];
		}

		if (NewViewTarget)
		{
			APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
			if (PC)
			{
				PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ViewTarget is null"));
		}
		
	}

	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}