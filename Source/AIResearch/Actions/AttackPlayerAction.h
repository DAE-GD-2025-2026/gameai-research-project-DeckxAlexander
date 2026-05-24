// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIResearch/GOAPAction.h"

#include "AttackPlayerAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
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
		m_Effects.Add("Alerted", false);
		m_Effects.Add("HasAmmo", false);
		m_FailedEffects.Add("HasAmmo", false);
	}
	
	void OnProjectileHit(AActor* OtherActor);
	void OnProjectileFail();
	
	virtual void Start( AGOAPAIController* Controller) override;
	virtual void Tick( AGOAPAIController* Controller, float DeltaTime) override;
	
private:
	APawn* m_PlayerCharacter{};
	AGOAPAIController* m_Controller{};
	
};
