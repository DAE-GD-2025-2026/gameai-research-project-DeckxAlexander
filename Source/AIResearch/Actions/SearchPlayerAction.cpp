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

	auto distance = (Controller->GetPawn()->GetActorLocation() - m_PlayerCharacter->GetActorLocation()).Length();
	// If AI sees the player
	if (Controller->CanSeePlayer(m_PlayerCharacter) && distance <= 2000)
	{
		Controller->StopMovement();
		Controller->ProcessSuccess();
	}
	else
	{
		// Move toward player until visible
		Controller->MoveToActor(m_PlayerCharacter, 100.f);
	}
	
}
