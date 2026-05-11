
#include "ActionPlanner.h"

float ActionPlanner::Heuristic(const FWorldState& state, const FWorldState& goal) 
{
    float cost = 0.f;
    for (const auto& goalstate : goal)
    {
        if (!state.Contains(goalstate.Key) || state[goalstate.Key] != goalstate.Value)
        {
            cost += 1.f;
        }
    }

    return cost;
}

bool ActionPlanner::HasReachedGoal(const FWorldState& state, const FWorldState& goal) 
{
	for (const auto& gstate : goal)
	{
		if (!state.Contains(gstate.Key) || state[gstate.Key] != gstate.Value)
		{
			return false;
		}
	}
	return true;
}

TArray<UGOAPAction*> ActionPlanner::PlanAStar(const FWorldState& start, const FWorldState& goal,
                                              const TArray<UGOAPAction*>& possibleActions)
{
	
	TArray<FGoapNode> openSet;
	
	//Create StartNode
	FGoapNode startNode;
	startNode.State = start;
	startNode.GCost = 0.f;
	startNode.HCost = Heuristic(start, goal);
	startNode.RemainingActions = possibleActions;
	
	openSet.Add(startNode);
	
	TArray<UGOAPAction*> bestPlan;
	float bestCost = FLT_MAX;
	
	while (openSet.Num() > 0)
	{
		openSet.Sort([](const FGoapNode& A, const FGoapNode& B)
			{return A.FCost() < B.FCost();});
		
		FGoapNode current = openSet[0];
		openSet.RemoveAt(0);
		
		//Gcost worst then best cost = skip
		if (current.GCost >= bestCost) continue;
		
		if (HasReachedGoal(current.State, goal))
		{
			bestCost = current.GCost;
			bestPlan = current.Plan;
			continue;
		}
		
		for (UGOAPAction* action : current.RemainingActions)
		{
			if (action == nullptr) continue;
			if (!action->IsApplicable(current.State)) continue; //If action is not applicable to the current state
			
			auto newState = current.State;
			action->Apply(newState);
			
			FGoapNode childNode;
			childNode.State = newState;
			
			childNode.GCost = current.GCost + action->GetCost();
			childNode.HCost = Heuristic(newState, goal);
			
			childNode.RemainingActions = current.RemainingActions;
			childNode.RemainingActions.Remove(action);
			
			childNode.Plan = current.Plan;
			childNode.Plan.Add(action);
			
			openSet.Add(childNode);
			

		}
		
		
	}
	
	
	
	
	
	return bestPlan;
	
	
	
}
