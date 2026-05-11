// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPAction.h"

bool UGOAPAction::IsApplicable(const FWorldState& State) const
{
	for (const auto& preCond : m_Preconditions)
	{
		if (!State.Contains(preCond.Key) || State[preCond.Key] != preCond.Value)
			return false;
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
