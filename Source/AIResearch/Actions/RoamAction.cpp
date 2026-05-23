// Fill out your copyright notice in the Description page of Project Settings.


#include "RoamAction.h"
#include "NavigationSystem.h"
#include "AIResearch/GOAPAIController.h"

void URoamAction::Start(AGOAPAIController* Controller)
{
	Super::Start(Controller);
	PickNewRoamLocation(Controller);
}

void URoamAction::Tick(AGOAPAIController* Controller, float DeltaTime)
{
	Super::Tick(Controller, DeltaTime);
	if (!Controller)
		return;
	APawn* ControlledPawn = Controller->GetPawn();
	if (!ControlledPawn) return;
	const float Distance =FVector::Dist(ControlledPawn->GetActorLocation(),m_TargetLocation);
	
	if (Distance <= 100.f)
	{
		PickNewRoamLocation(Controller);
	}
}

void URoamAction::PickNewRoamLocation(AGOAPAIController* Controller)
{
	if (!Controller)
		return;

	APawn* ControlledPawn = Controller->GetPawn();

	if (!ControlledPawn)
		return;

	UNavigationSystemV1* NavSystem =FNavigationSystem::GetCurrent<UNavigationSystemV1>(Controller->GetWorld());

	if (!NavSystem)return;

	FNavLocation RandomLocation;

	if (NavSystem->GetRandomReachablePointInRadius(ControlledPawn->GetActorLocation(),m_RoamRadius,RandomLocation))
	{
		m_TargetLocation = RandomLocation.Location;
		Controller->MoveToLocation(m_TargetLocation);
	}
}
