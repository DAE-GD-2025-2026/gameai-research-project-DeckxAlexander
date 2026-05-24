// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchHazardAction.h"

#include "AIResearch/GOAPAIController.h"
#include "AIResearch/HazardActor.h"
#include "AIResearch/MainGamemode.h"
#include "Kismet/GameplayStatics.h"

void USearchHazardAction::Start(AGOAPAIController* Controller)
{
	Super::Start(Controller);
	if (!GetClosestHazard(Controller,Controller->GetPawn()->GetActorLocation())) Controller->ProcessFailure();
	
	if (!IsValid(Controller->GetPawn()))return;
	
	
	EPathFollowingRequestResult::Type Result = Controller->MoveToLocation(m_HazardActor->GetActorLocation(),5.0f);
}

void USearchHazardAction::Tick(AGOAPAIController* Controller, float DeltaTime)
{
	if (!IsValid(m_HazardActor) )
	{
		Controller->StopMovement();
		if (!GetClosestHazard(Controller,Controller->GetPawn()->GetActorLocation()))
		{
			Controller->ProcessFailure();
			return;
		}
		
		Controller->MoveToLocation(m_HazardActor->GetActorLocation(),5.0f,true,true,false,true);
	}
}

void USearchHazardAction::OnOverlap(AGOAPAIController* Controller, AActor* OtherActor)
{
	Super::OnOverlap(Controller, OtherActor);
	
	
	if (IsValid(OtherActor) && OtherActor->IsA(AHazardActor::StaticClass()))
	{
		OtherActor->Destroy();
		Controller->ProcessSuccess();
		//AMainGamemode* gamemode = Cast<AMainGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
		//gamemode->CheckAmounts();

	}
}

bool USearchHazardAction::GetClosestHazard(AGOAPAIController* Controller, FVector location)
{
	auto world = Controller->GetWorld();

	
	TArray<AActor*> FoundActors{};
	UGameplayStatics::GetAllActorsOfClass(world,AHazardActor::StaticClass(),FoundActors);

	if (FoundActors.IsEmpty()) return false;
	
	AActor* closestActor = nullptr;
	float closestDistanceSq = FLT_MAX;

	for (AActor* Actor : FoundActors)
	{
		if (!Actor) continue;

		float DistanceSq = FVector::DistSquared(location,Actor->GetActorLocation());

		if (DistanceSq < closestDistanceSq)
		{
			closestDistanceSq = DistanceSq;
			closestActor = Actor;
		}
	}

	m_HazardActor = closestActor;
	return true;
}
