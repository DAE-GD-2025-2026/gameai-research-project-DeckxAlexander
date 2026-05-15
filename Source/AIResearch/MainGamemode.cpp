// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGamemode.h"

#include "AmmoActor.h"
#include "GOAPAIController.h"
#include "MeleeActor.h"
#include "GOAP/ActionPlanner.h"
#include "Actions/AttackPlayerAction.h"
#include "Actions/SearchAmmoAction.h"
#include "Actions/SearchPlayerAction.h"
#include "Kismet/GameplayStatics.h"

void AMainGamemode::BeginPlay()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AGOAPAIController::StaticClass(),Actors);
	
	for (auto actor : Actors)
	{
		m_Controllers.Add(Cast<AGOAPAIController>(actor));
	}
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AMeleeActor::StaticClass(),Actors);
	AmountOfMelee = Actors.Num();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AAmmoActor::StaticClass(),Actors);
	AmountOfAmmo = Actors.Num();
	
	if (AmountOfMelee <= 0)SetWorldState({{FName("MeleeInScene"), false}});
	else SetWorldState({{FName("MeleeInScene"), true}});
	
	if (AmountOfAmmo <= 0)
		SetWorldState({{FName("AmmoInScene"), false}});
	else SetWorldState({{FName("AmmoInScene"), true}});
	
	
	//Start all controllers!
	for (auto controller : m_Controllers)
	{
		controller->StartGOAP();
	}
}

void AMainGamemode::SetWorldState(TMap<FName, bool> state)
{
	for (auto s : state)
	{
		WorldState.Add(s.Key, s.Value);
	}
	AlertWorldStateControllers();
}

void AMainGamemode::AlertWorldStateControllers()
{
	if (WorldState.IsEmpty()) return;
	for (auto controller : m_Controllers)
	{
		
		controller->SetState(WorldState);
	}
	
	
}

void AMainGamemode::CheckAmounts()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AMeleeActor::StaticClass(),Actors);
	AmountOfMelee = Actors.Num();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AAmmoActor::StaticClass(),Actors);
	AmountOfAmmo = Actors.Num();
	
	if (AmountOfMelee <= 0)
	{
		SetWorldState({{FName("MeleeInScene"), false}});
	}
	
	if (AmountOfAmmo <= 0)
	{
		SetWorldState({{FName("AmmoInScene"), false}});
	}
}
