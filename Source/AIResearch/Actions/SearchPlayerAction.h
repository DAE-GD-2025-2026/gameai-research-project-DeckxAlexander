// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIResearch/GOAPAction.h"
#include "SearchPlayerAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AIRESEARCH_API USearchPlayerAction : public UGOAPAction
{
	GENERATED_BODY()
public:
	USearchPlayerAction()
	{
		m_Preconditions.Add("HasAmmo", true);
		m_Preconditions.Add("SeePlayer", false);
		m_Preconditions.Add("PAlive", true);
		m_Effects.Add("SeePlayer", true);
	}
	
	virtual void Start( AGOAPAIController* Controller) override;
	virtual void Tick( AGOAPAIController* Controller, float DeltaTime) override;
	
private:
	APawn* m_PlayerCharacter{};
};
