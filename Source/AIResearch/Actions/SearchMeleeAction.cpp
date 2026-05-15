// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchMeleeAction.h"
#include "Kismet/GameplayStatics.h"
#include "AIResearch/GOAPAIController.h"
#include "AIResearch/MainGamemode.h"
#include "AIResearch/MeleeActor.h"

void USearchMeleeAction::Start(AGOAPAIController* Controller)
{
	Super::Start(Controller);
	if (!GetClosestMelee(Controller->GetWorld(),Controller->GetPawn()->GetActorLocation())) Controller->ProcessFailure();
	
	if (!IsValid(Controller->GetPawn()))return;
	
	
	EPathFollowingRequestResult::Type Result = Controller->MoveToLocation(m_TargetAmmo->GetActorLocation(),5.0f);
}

void USearchMeleeAction::Tick(AGOAPAIController* Controller, float DeltaTime)
{
	Super::Tick(Controller, DeltaTime);
	if (!IsValid(m_TargetAmmo) )
	{
		Controller->StopMovement();
		if (!GetClosestMelee(Controller->GetWorld(),Controller->GetPawn()->GetActorLocation()))
		{
			Controller->ProcessFailure();
			return;
		}
		
		Controller->MoveToLocation(m_TargetAmmo->GetActorLocation(),5.0f,true,true,false,true);
	}
}

void USearchMeleeAction::OnOverlap(AGOAPAIController* Controller, AActor* OtherActor)
{
	Super::OnOverlap(Controller, OtherActor);
	
	
	if (IsValid(OtherActor) && OtherActor->IsA(AMeleeActor::StaticClass()))
	{
		OtherActor->Destroy();
		Controller->ProcessSuccess();
		AMainGamemode* gamemode = Cast<AMainGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
		gamemode->CheckAmounts();

	}
}

bool USearchMeleeAction::GetClosestMelee(UObject* world, FVector location)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(world,AMeleeActor::StaticClass(),FoundActors);

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

	m_TargetAmmo = closestActor;
	return true;
}
