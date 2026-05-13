// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGamemode.h"

#include "GOAPAIController.h"
#include "GOAP/ActionPlanner.h"
#include "Actions/AttackPlayerAction.h"
#include "Actions/SearchAmmoAction.h"
#include "Actions/SearchPlayerAction.h"
#include "Kismet/GameplayStatics.h"

void AMainGamemode::BeginPlay()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		AGOAPAIController::StaticClass(),
		Actors
	);
	
	for (auto actor : Actors)
	{
		m_Controllers.Add(Cast<AGOAPAIController>(actor));
	}
}

void AMainGamemode::SetWorldState(TMap<FName, bool> state)
{
	for (const auto& s : state)
	{
		WorldState.Add(s.Key, s.Value);
	}
	AlertWorldStateControllers();
}

void AMainGamemode::AlertWorldStateControllers()
{
	for (auto controller : m_Controllers)
	{
		controller->SetState(WorldState);
	}
	
	
}
