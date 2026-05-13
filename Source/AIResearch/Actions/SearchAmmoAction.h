// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIResearch/GOAPAction.h"
#include "SearchAmmoAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AIRESEARCH_API USearchAmmoAction : public UGOAPAction
{
	GENERATED_BODY()
public:
	USearchAmmoAction()
	{
		m_Preconditions.Add("HasAmmo", false);
		m_Effects.Add("HasAmmo", true);
	}
	virtual void Start( AGOAPAIController* Controller) override;
	virtual void Tick( AGOAPAIController* Controller, float DeltaTime) override;
	virtual void OnOverlap(AGOAPAIController* Controller, AActor* OtherActor) override;
	
private:
	bool GetClosestAmmo(UObject* world, FVector location);
	AActor* m_TargetAmmo{};
};
