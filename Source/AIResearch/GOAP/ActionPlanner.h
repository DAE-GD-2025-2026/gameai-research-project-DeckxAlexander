#pragma once
#include "AIResearch/GOAPAction.h"


struct FGoapNode
{
	FWorldState State;

	float GCost = 0.f;
	float HCost = 0.f;

	TArray<UGOAPAction*> Plan;
	TArray<UGOAPAction*> RemainingActions;

	float FCost() const { return GCost + HCost; }
};

class ActionPlanner
{
public:
	float Heuristic(const FWorldState& state, const FWorldState& goal);
	bool HasReachedGoal(const FWorldState& state, const FWorldState& goal);
	TArray<UGOAPAction*> PlanAStar(const FWorldState& start, const FWorldState& goal, const TArray<UGOAPAction*>& possibleActions);
	
};
