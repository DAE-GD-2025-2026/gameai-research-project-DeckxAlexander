// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIResearch/GOAPAction.h"
#include "RemoveHazardAction.generated.h"

/**
 * 
 */
UCLASS()
class AIRESEARCH_API URemoveHazardAction : public UGOAPAction
{
	GENERATED_BODY()
public:
	URemoveHazardAction()
	{
		m_Preconditions.Add("HoldsHazard", true);
		m_Preconditions.Add("Alerted", false);
		m_Effects.Add("HoldsHazard", false);
		m_Effects.Add("HazardInArea", false);
		m_FailedEffects.Add("HoldsHazard", false);
	}
	virtual void Start(AGOAPAIController* Controller) override;
	virtual void Tick(AGOAPAIController* Controller, float DeltaTime) override;

private:
	AActor* m_GarbageActor{};
};
