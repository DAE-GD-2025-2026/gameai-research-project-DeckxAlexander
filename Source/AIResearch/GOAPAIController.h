// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GOAPAction.h"
#include "GOAPAIController.generated.h"

class UGOAPAction;
/**
 * 
 */
UCLASS()
class AIRESEARCH_API AGOAPAIController : public AAIController
{
	GENERATED_BODY()
public:
	AGOAPAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	
	
	void ProcessSuccess();
	void ProcessFailure();
	void ProcessWorldStateChanged();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()	
	UBlackboardComponent* BlackboardComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Action Planner")
	TMap<FName,bool> StartState{};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Action Planner")
	TMap<FName,bool> GoalState{};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Action Planner")
	UGOAPAction* CurrentAction{};
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Action Planner")
	TArray<UGOAPAction*> ActivePlan{};
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Instanced, Category="Action Planner")
	TArray<UGOAPAction*> AvailableActions{};
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Instanced, Category="Action Planner")
	UGOAPAction* IdleAction{};
	
	void CalculatePlan();
	void ExecuteNext();

	
	
	
	
	
};