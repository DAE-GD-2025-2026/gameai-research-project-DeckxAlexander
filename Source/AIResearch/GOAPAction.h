// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GOAPAction.generated.h"

using FWorldState = TMap<FName, bool>;
class AGOAPAIController;
UCLASS(Abstract, Blueprintable, EditInlineNew)
class AIRESEARCH_API UGOAPAction : public UObject
{
	GENERATED_BODY()
public:
	bool IsApplicable(const FWorldState& State) const;
	void Apply(FWorldState& State) const;
	float GetCost() const {return m_Cost;}
	//Functions to override
	virtual void Start( AGOAPAIController* Controller) {}
	virtual void Tick( AGOAPAIController* Controller, float DeltaTime) {}
	virtual void OnOverlap(AGOAPAIController* Controller, AActor* OtherActor) {}
	virtual void Reset() {}
protected:
	FWorldState m_Preconditions{};
	FWorldState m_Effects{};
	float m_Cost{1.f};
	static FVector GetRandomReachablePoint(UObject* WorldContextObject, FVector Origin, float Radius);
	
	
};
