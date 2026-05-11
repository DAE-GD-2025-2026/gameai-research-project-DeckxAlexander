// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIResearch/GOAPAction.h"
#include "AttackPlayerAction.generated.h"

/**
 * 
 */
UCLASS()
class AIRESEARCH_API UAttackPlayerAction : public UGOAPAction
{
	GENERATED_BODY()
public:
	UAttackPlayerAction()
	{
		m_Preconditions.Add("HasAmmo", true);
		m_Preconditions.Add("SeePlayer", true);
		m_Preconditions.Add("PAlive", true);
		m_Effects.Add("PAlive", false);
	}
};
