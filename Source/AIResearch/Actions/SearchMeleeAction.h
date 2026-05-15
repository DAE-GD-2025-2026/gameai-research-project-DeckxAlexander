// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIResearch/GOAPAction.h"
#include "SearchMeleeAction.generated.h"

/**
 * 
 */
UCLASS()
class AIRESEARCH_API USearchMeleeAction : public UGOAPAction
{
	GENERATED_BODY()
public:
	USearchMeleeAction()
	{
		m_Preconditions.Add("HasMelee", false);
		m_Preconditions.Add("MeleeInScene", true);
		m_Effects.Add("HasMelee", true);
	}
	virtual void Start( AGOAPAIController* Controller) override;
	virtual void Tick( AGOAPAIController* Controller, float DeltaTime) override;
	virtual void OnOverlap(AGOAPAIController* Controller, AActor* OtherActor) override;
	
private:
	bool GetClosestMelee(UObject* world, FVector location);
	AActor* m_TargetAmmo{};
	
};
