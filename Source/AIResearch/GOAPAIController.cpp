// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPAIController.h"
#include "GOAP/ActionPlanner.h"
#include "Kismet/GameplayStatics.h"
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
	m_PlayerCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
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
	
	if (State["SeePlayer"] == true && !CanSeePlayer(m_PlayerCharacter))
	{
		State["SeePlayer"] = false;
	}
	
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
	CurrentAction->ApplyFailed(State);
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

	
	if ((start-end).Length() > 1000) return false;
	
	
	float radius = 50.f;

	FHitResult hit;

	FCollisionQueryParams params;
	params.AddIgnoredActor(GetPawn());

	bool bHit = GetWorld()->SweepSingleByChannel(hit,start,end,FQuat::Identity,ECC_Visibility,FCollisionShape::MakeSphere(radius),params);
	
	return (bHit == true && hit.GetActor() == PlayerPawn) || !bHit;
}

void AGOAPAIController::SetState(TMap<FName, bool> state)
{
	for (const auto& s : state)
	{
		State.Add(s.Key, s.Value);
	}
	
	if (CurrentAction->IsApplicable(State)) return;
	
	StopMovement();
	
	CurrentAction = IdleAction;	
	CalculatePlan();

	
}
