// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPAction.h"
#include "NavigationSystem.h"
#include "NavigationSystemTypes.h"
#include "NavFilters/NavigationQueryFilter.h"


bool UGOAPAction::IsApplicable(const FWorldState& State) const
{
	for (const auto& preCond : m_Preconditions)
	{
		const auto* ValuePtr = State.Find(preCond.Key);
		if (!ValuePtr || *ValuePtr != preCond.Value)
		{
			return false;
		}
	}
	return true;
}

void UGOAPAction::Apply(FWorldState& State) const
{
	for (const auto& effect : m_Effects)
	{
		State.Add(effect.Key, effect.Value);
	}
}


