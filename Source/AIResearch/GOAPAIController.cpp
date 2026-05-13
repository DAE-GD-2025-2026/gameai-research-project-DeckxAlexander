// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPAIController.h"
#include "GOAP/ActionPlanner.h"
#include "BehaviorTree/BlackboardComponent.h"


AGOAPAIController::AGOAPAIController() 
{
	PrimaryActorTick.bCanEverTick = true;
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	State.Add(FName("PAlive"), true);
	State.Add(FName("HasAmmo"), false);
	State.Add(FName("SeePlayer"), false);
	
	GoalState.Add(FName("PAlive"), false);
}

void AGOAPAIController::BeginPlay()
{
	Super::BeginPlay(); //Calculate First Path
}

void AGOAPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);  
	
}

void AGOAPAIController::CalculatePlan()
{
	if (GoalState.IsEmpty() || State.IsEmpty() || AvailableActions.IsEmpty()) return;
	CurrentAction = IdleAction;
	ActivePlan.Empty();
	
	ActivePlan = ActionPlanner::PlanAStar(State,GoalState,AvailableActions);
	
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

void AGOAPAIController::StartGOAP()
{
	if (IdleAction == nullptr) return;
	CalculatePlan();
}

void AGOAPAIController::ExecuteNext()
{

	CurrentAction = IdleAction;
	if (!ActivePlan.IsEmpty())
	{
		CurrentAction = ActivePlan[0];
		ActivePlan.RemoveAt(0);
		if (!CurrentAction->IsApplicable(State))
		{
			CalculatePlan();
			return;
		}
	}
	CurrentAction->Start(this);
}

void AGOAPAIController::ProcessSuccess()
{
	CurrentAction->Apply(State);
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

void AGOAPAIController::ProcessOverlap(AActor* OtherActor)
{
	CurrentAction->OnOverlap(this, OtherActor);
}

bool AGOAPAIController::CanSeePlayer(APawn* PlayerPawn) const
{
	if (!PlayerPawn || !GetPawn())
		return false;

	FVector start = GetPawn()->GetActorLocation();

	FVector end = PlayerPawn->GetActorLocation();


	float radius = 50.f;

	FHitResult hit;

	FCollisionQueryParams params;
	params.AddIgnoredActor(GetPawn());

	bool bHit = GetWorld()->SweepSingleByChannel(
		hit,
		start,
		end,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeSphere(radius),
		params
	);

	// If sphere trace hits player first -> visible
	return !bHit;
}
