#include "C:\Users\alexa\Desktop\gameai-research-project-DeckxAlexander\Intermediate\Build\Win64\x64\AIResearchEditor\Development\UnrealEd\SharedPCH.UnrealEd.Project.ValApi.ValExpApi.Cpp20.InclOrderUnreal5_4.h"
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
		//Sort by FCost
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
		
		//Continue....
	}
	
	
	
	
	
	return bestPlan;
	
	
	
}
