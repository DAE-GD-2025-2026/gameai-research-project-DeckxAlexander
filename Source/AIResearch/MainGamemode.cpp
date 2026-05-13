// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGamemode.h"
#include "GOAP/ActionPlanner.h"
#include "Actions/AttackPlayerAction.h"
#include "Actions/SearchAmmoAction.h"
#include "Actions/SearchPlayerAction.h"

void AMainGamemode::BeginPlay()
{
	Super::BeginPlay();



	 TMap<FName, bool> Start{};

	Start.Add(FName("PAlive"), true);
	Start.Add(FName("HasAmmo"), false);
	Start.Add(FName("SeePlayer"), false);

	

	FWorldState Goal{};

	Goal.Add(FName("PAlive"), false);
	TArray<UGOAPAction*> Actions{};

	Actions.Add(NewObject<USearchAmmoAction>(this));
	Actions.Add(NewObject<USearchPlayerAction>(this));
	Actions.Add(NewObject<UAttackPlayerAction>(this));
	
	TArray<UGOAPAction*> Plan = ActionPlanner::PlanAStar(Start,Goal,Actions);
	UE_LOG(LogTemp, Warning,
		TEXT("====== GOAP PLAN ======"));

	if (Plan.Num() == 0)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("No Plan Found"));

		return;
	}

	for (int32 i = 0; i < Plan.Num(); i++)
	{
		UGOAPAction* Action = Plan[i];

		if (!Action)
		{
			continue;
		}

		UE_LOG(LogTemp, Warning,
			TEXT("%d: %s"),
			i,
			*Action->GetClass()->GetName());
	}
}
