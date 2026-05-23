// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIResearch/GOAPAction.h"
#include "RoamAction.generated.h"

/**
 * 
 */
UCLASS()
class AIRESEARCH_API URoamAction : public UGOAPAction
{
	GENERATED_BODY()
public:
	URoamAction()
	{
		m_Preconditions.Add("Alarm", false);
		m_Effects.Add("Alerted", true);
	}
	
	virtual void Start( AGOAPAIController* Controller) override;
	virtual void Tick( AGOAPAIController* Controller, float DeltaTime) override;
private:
	void PickNewRoamLocation(AGOAPAIController* Controller);
	FVector m_TargetLocation{};
	float m_RoamRadius = 1000.f;
};
