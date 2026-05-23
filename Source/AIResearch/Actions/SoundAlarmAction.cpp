// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundAlarmAction.h"
#include "Kismet/GameplayStatics.h"
#include "AIResearch/AlarmActor.h"
#include "NavigationSystem.h"
#include "AIResearch/GOAPAIController.h"


void USoundAlarmAction::Start(AGOAPAIController* Controller)
{
	Super::Start(Controller);
	m_AlarmActor = UGameplayStatics::GetActorOfClass(Controller->GetWorld(),AAlarmActor::StaticClass());
	UNavigationSystemV1* NavSystem =FNavigationSystem::GetCurrent<UNavigationSystemV1>(Controller->GetWorld());
	
	FNavLocation location{};
	NavSystem->GetRandomReachablePointInRadius(m_AlarmActor->GetActorLocation(),150.f,location);
	
	
	if (!m_AlarmActor)
	{
		Controller->ProcessFailure();
		return;
	}
	
	Controller->MoveToLocation(location.Location, 100.f);
}

void USoundAlarmAction::Tick(AGOAPAIController* Controller, float DeltaTime)
{
	Super::Tick(Controller, DeltaTime);
	if (!Controller || !m_AlarmActor) return;

	APawn* ControlledPawn = Controller->GetPawn();
	if (!ControlledPawn) return;

	const float Distance =FVector::Dist(ControlledPawn->GetActorLocation(),m_AlarmActor->GetActorLocation());

	// Reached alarm
	if (Distance <= 200.f)
	{
		Controller->ProcessSuccess();
		Cast<AAlarmActor>(m_AlarmActor)->SoundAlarm();

	}
	
}
