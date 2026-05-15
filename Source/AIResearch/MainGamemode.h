// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGamemode.generated.h"

/**
 * 
 */
class AGOAPAIController;
UCLASS()
class AIRESEARCH_API AMainGamemode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void SetWorldState(TMap<FName,bool> state);
	void CheckAmounts();

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Action Planner")
	TMap<FName,bool> WorldState{};
	
	void AlertWorldStateControllers();

	TArray<AGOAPAIController*> m_Controllers;
	int AmountOfAmmo = 0;
	int AmountOfMelee = 0;
	

};
