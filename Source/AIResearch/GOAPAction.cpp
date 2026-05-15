// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPAction.h"
#include "NavigationSystem.h"
#include "NavigationSystemTypes.h"
#include "NavFilters/NavigationQueryFilter.h"


bool UGOAPAction::IsApplicable(const FWorldState& State) const
{
	if (m_Preconditions.IsEmpty()) return true;
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
	if (m_Effects.IsEmpty()) return;
	for (const auto& effect : m_Effects)
	{
		State.Add(effect.Key, effect.Value);
	}
}

void UGOAPAction::ApplyFailed(FWorldState& State) const
{
	if (m_FailedEffects.IsEmpty()) return;
	for (const auto& effect : m_FailedEffects)
	{
		State.Add(effect.Key, effect.Value);
	}
}


