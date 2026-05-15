// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIResearch/GOAPAction.h"
#include "AttackMeleeAction.generated.h"

/**
 * 
 */
UCLASS()
class AIRESEARCH_API UAttackMeleeAction : public UGOAPAction
{
	GENERATED_BODY()
public:
	UAttackMeleeAction()
	{
		m_Preconditions.Add("HasMelee", true);
		m_Preconditions.Add("PAlive", true);
		m_Effects.Add("PAlive", false);
		m_Effects.Add("HasMelee", false);
		m_FailedEffects.Add("HasMelee", false);

		m_Cost = 10.f;
	}
	
	
	virtual void Start( AGOAPAIController* Controller) override;
	virtual void Tick( AGOAPAIController* Controller, float DeltaTime) override;
	
private:
	APawn* m_PlayerCharacter{};
	AGOAPAIController* m_Controller{};
	
	bool AttackSphere(AGOAPAIController* Controller);
};
