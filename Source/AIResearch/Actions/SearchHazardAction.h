// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIResearch/GOAPAction.h"
#include "SearchHazardAction.generated.h"

/**
 * 
 */
UCLASS()
class AIRESEARCH_API USearchHazardAction : public UGOAPAction
{
	GENERATED_BODY()
public:
	USearchHazardAction()
	{
		m_Preconditions.Add("HoldsHazard", false);
		m_Preconditions.Add("HazardInScene", true);
		m_Preconditions.Add("Alerted", false);
		m_Effects.Add("HoldsHazard", true);
		m_FailedEffects.Add("HazardInScene", false);
	}
	
	virtual void Start(AGOAPAIController* Controller) override;
	virtual void Tick(AGOAPAIController* Controller, float DeltaTime) override;
	virtual void OnOverlap(AGOAPAIController* Controller, AActor* OtherActor) override;

private:
	AActor* m_HazardActor{};
	
	bool GetClosestHazard(AGOAPAIController* Controller, FVector location);
};
