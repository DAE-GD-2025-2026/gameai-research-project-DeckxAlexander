// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchAmmoAction.h"

#include "AIController.h"
#include "AIResearch/AmmoActor.h"
#include "Kismet/GameplayStatics.h"
#include "AIResearch/GOAPAIController.h"

void USearchAmmoAction::Start( AGOAPAIController* Controller)
{
	Super::Start(Controller);
	if (!GetClosestAmmo(Controller->GetWorld(),Controller->GetPawn()->GetActorLocation())) Controller->ProcessFailure();
	
	if (!IsValid(Controller->GetPawn()))return;
	
	
	EPathFollowingRequestResult::Type Result =
	Controller->MoveToLocation(m_TargetAmmo->GetActorLocation(),5.0f);

	UE_LOG(LogTemp, Warning, TEXT("Move result: %d"), Result);
}

void USearchAmmoAction::Tick( AGOAPAIController* Controller, float DeltaTime)
{
	Super::Tick(Controller, DeltaTime);
	if (!IsValid(m_TargetAmmo) )
	{
		Controller->StopMovement();
		if (!GetClosestAmmo(Controller->GetWorld(),Controller->GetPawn()->GetActorLocation()))
		{
			Controller->ProcessFailure();
			return;
		}
		
		Controller->MoveToLocation(m_TargetAmmo->GetActorLocation(),5.0f,true,true,false,true);
	}
	
}

void USearchAmmoAction::OnOverlap(AGOAPAIController* Controller, AActor* OtherActor)
{
	Super::OnOverlap(Controller, OtherActor);
	if (OtherActor->IsA(AAmmoActor::StaticClass()))
	{
		OtherActor->Destroy();
		Controller->ProcessSuccess();
	}
	
}

bool USearchAmmoAction::GetClosestAmmo(UObject* world, FVector location)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(world,AAmmoActor::StaticClass(),FoundActors);

	if (FoundActors.IsEmpty()) return false;
	
	AActor* closestActor = nullptr;
	float closestDistanceSq = FLT_MAX;

	for (AActor* Actor : FoundActors)
	{
		if (!Actor)
			continue;

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




