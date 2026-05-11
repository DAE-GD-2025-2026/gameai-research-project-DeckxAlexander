// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GOAPAction.generated.h"

using FWorldState = TMap<FName, bool>;
UCLASS()
class AIRESEARCH_API UGOAPAction : public UObject
{
	GENERATED_BODY()
public:
	bool IsApplicable(const FWorldState& State) const;
	void Apply(FWorldState& State) const;
	float GetCost() const {return m_Cost;}
	//Functions to override
	virtual void Start(class AAIController* Controller) {}
	virtual void Tick(class AAIController* Controller, float DeltaTime) {}
	virtual bool IsFinished() const { return true; }
	virtual void Reset() {}
protected:
	FWorldState m_Preconditions{};
	FWorldState m_Effects{};
	float m_Cost{1.f};
	
	
	
};
