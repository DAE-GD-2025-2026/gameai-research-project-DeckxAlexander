// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIResearch/GOAPAction.h"
#include "SearchAmmoAction.generated.h"

/**
 * 
 */
UCLASS()
class AIRESEARCH_API USearchAmmoAction : public UGOAPAction
{
	GENERATED_BODY()
public:
	USearchAmmoAction()
	{
		m_Preconditions.Add("HasAmmo", false);
		m_Effects.Add("HasAmmo", true);
	}
	
};
