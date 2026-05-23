// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIResearch/GOAPAction.h"
#include "SoundAlarmAction.generated.h"

/**
 * 
 */
UCLASS()
class AIRESEARCH_API USoundAlarmAction : public UGOAPAction
{
	GENERATED_BODY()
public:
	USoundAlarmAction()
	{
		m_Preconditions.Add("Alerted", true);

		m_Effects.Add("Alarm", true);
	}

	virtual void Start(AGOAPAIController* Controller) override;
	virtual void Tick(AGOAPAIController* Controller, float DeltaTime) override;

private:
	
	
	AActor* m_AlarmActor{};
	
};
