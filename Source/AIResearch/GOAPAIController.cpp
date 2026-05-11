// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPAIController.h"
#include "GOAP/ActionPlanner.h"
#include "BehaviorTree/BlackboardComponent.h"


AGOAPAIController::AGOAPAIController() 
{
	PrimaryActorTick.bCanEverTick = true;
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	StartState.Add(FName("PAlive"), true);
	StartState.Add(FName("HasAmmo"), false);
	StartState.Add(FName("SeePlayer"), false);
	
	GoalState.Add(FName("PAlive"), false);
}

void AGOAPAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AGOAPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (IdleAction == nullptr) throw; //No idle exception is unsafe
	
	CalculatePlan(); 	//Calculate First Path
	
}

void AGOAPAIController::CalculatePlan()
{
	if (GoalState.IsEmpty() || StartState.IsEmpty() || AvailableActions.IsEmpty()) return;
	CurrentAction = IdleAction;
	ActivePlan.Empty();
	
	ActivePlan = ActionPlanner::PlanAStar(StartState,GoalState,AvailableActions);
	
	if (!ActivePlan.IsEmpty())
	{
		CurrentAction = ActivePlan[0];
		ActivePlan.RemoveAt(0);
	}
	CurrentAction->Start(this);
	
	
}

void AGOAPAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CurrentAction == nullptr) return;
	CurrentAction->Tick(this, DeltaSeconds);
}

void AGOAPAIController::ExecuteNext()
{
	CurrentAction = IdleAction;
	if (!ActivePlan.IsEmpty())
	{
		CurrentAction = ActivePlan[0];
		ActivePlan.RemoveAt(0);
	}
	CurrentAction->Start(this);
}

void AGOAPAIController::ProcessSuccess()
{
	ExecuteNext();
}

void AGOAPAIController::ProcessFailure()
{
	CalculatePlan(); //Recalculate On Failure
}

void AGOAPAIController::ProcessWorldStateChanged()
{
	CalculatePlan(); //Recalculate On Worldstate changed
}
