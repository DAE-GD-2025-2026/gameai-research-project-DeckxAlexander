// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GOAPAction.h"
#include "GOAPAIController.generated.h"
class AProjectileActor;

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
	
	UFUNCTION(BlueprintCallable)
	void StartGOAP();
	
	void ProcessSuccess();
	void ProcessFailure();
	void ProcessWorldStateChanged();
	
	UFUNCTION(BlueprintCallable)
	void ProcessOverlap(AActor* OtherActor);

	
	bool CanSeePlayer(APawn* PlayerPawn) const;
	
	void SetState(TMap<FName,bool> state);
	
	void SetGoalState(TMap<FName,bool> state);
		
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Attacking")
	TSubclassOf<AProjectileActor> ProjectileClass;
	
	UGOAPAction* GetCurrentAction() const { return CurrentAction; }
	TMap<FName,bool> GetCurrentState() const { return State; }
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()	
	UBlackboardComponent* BlackboardComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Action Planner")
	TMap<FName,bool> State{};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Action Planner")
	TMap<FName,bool> GoalState{};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Action Planner")
	UGOAPAction* CurrentAction{};
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Action Planner")
	TArray<UGOAPAction*> ActivePlan{};
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Instanced, Category="Action Planner")
	TArray<UGOAPAction*> AvailableActions;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Instanced, Category="Action Planner")
	UGOAPAction* IdleAction{};

	APawn* m_PlayerCharacter{};
	
	void CalculatePlan();
	void ExecuteNext();
	
	

	
	
	
	
	
};