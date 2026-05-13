// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchPlayerAction.h"
#include "Kismet/GameplayStatics.h"
#include "AIResearch/GOAPAIController.h"

void USearchPlayerAction::Start(AGOAPAIController* Controller)
{
	Super::Start(Controller);
	
	m_PlayerCharacter = UGameplayStatics::GetPlayerPawn(Controller->GetWorld(), 0);
	
}

void USearchPlayerAction::Tick(AGOAPAIController* Controller, float DeltaTime)
{
	Super::Tick(Controller, DeltaTime);
	
	if (!m_PlayerCharacter)
		return;
	
	// If AI sees the player
	if (Controller->CanSeePlayer(m_PlayerCharacter) )
	{
		Controller->StopMovement();
		Controller->ProcessSuccess();
	}
	else
	{
		// Move toward player until visible
		Controller->MoveToActor(m_PlayerCharacter, 20.f);
	}
	
}
