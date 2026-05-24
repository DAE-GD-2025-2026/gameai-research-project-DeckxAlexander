// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoveHazardAction.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "AIResearch/GarbageActor.h"
#include "AIResearch/GOAPAIController.h"
#include "AIResearch/MainGamemode.h"

void URemoveHazardAction::Start(AGOAPAIController* Controller)
{
	Super::Start(Controller);
	m_GarbageActor = UGameplayStatics::GetActorOfClass(Controller->GetWorld(),AGarbageActor::StaticClass());
	UNavigationSystemV1* NavSystem =FNavigationSystem::GetCurrent<UNavigationSystemV1>(Controller->GetWorld());
	
	FNavLocation location{};
	NavSystem->GetRandomReachablePointInRadius(m_GarbageActor->GetActorLocation(),150.f,location);
	
	
	if (!m_GarbageActor)
	{
		Controller->ProcessFailure();
		return;
	}
	
	Controller->MoveToLocation(location.Location, 100.f);
}

void URemoveHazardAction::Tick(AGOAPAIController* Controller, float DeltaTime)
{
	Super::Tick(Controller, DeltaTime);
	if (!Controller || !m_GarbageActor) return;

	APawn* ControlledPawn = Controller->GetPawn();
	if (!ControlledPawn) return;

	const float Distance =FVector::Dist(ControlledPawn->GetActorLocation(),m_GarbageActor->GetActorLocation());

	// Reached alarm
	if (Distance <= 300.f)
	{
		AMainGamemode* gamemode = Cast<AMainGamemode>(UGameplayStatics::GetGameMode(GetWorld()));

		
		if (gamemode->CheckHazards() > 0)
		{
			Controller->ProcessFailure();
		}
		else
		{
			Controller->ProcessSuccess();
			gamemode->CheckAmounts();
		}

	}
}
