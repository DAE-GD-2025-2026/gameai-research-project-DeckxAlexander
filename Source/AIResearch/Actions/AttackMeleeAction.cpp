// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackMeleeAction.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIResearch/GOAPAIController.h"
#include "GameFramework/Character.h"
#include "AIResearch/MainGamemode.h"

void UAttackMeleeAction::Start(AGOAPAIController* Controller)
{
	Super::Start(Controller);

	m_PlayerCharacter = UGameplayStatics::GetPlayerPawn(Controller->GetWorld(), 0);
	m_Controller = Controller;

	FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(Controller->GetPawn()->GetActorLocation(),m_PlayerCharacter->GetActorLocation());

	Controller->GetPawn()->SetActorRotation(LookAt);




}

void UAttackMeleeAction::Tick(AGOAPAIController* Controller, float DeltaTime)
{
	Super::Tick(Controller, DeltaTime);
	
	if (!IsValid(m_PlayerCharacter))
	{
		Controller->StopMovement();
		Controller->ProcessFailure();
		return;
	}
		
	
	float distance = (Controller->GetPawn()->GetActorLocation()-m_PlayerCharacter->GetActorLocation()).Length();
	
	if (distance < 300.f )
	{
		Controller->StopMovement();
		if (AttackSphere(Controller))
		{
			Controller->ProcessSuccess();
			AMainGamemode* gamemode = Cast<AMainGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
			gamemode->SetWorldState(m_Effects);
			m_PlayerCharacter->Destroy();
			return;
		}
		else Controller->ProcessFailure();
	}
	else
	{
		Controller->MoveToActor(m_PlayerCharacter, 20.f);
	}
}

bool UAttackMeleeAction::AttackSphere(AGOAPAIController* Controller)
{
	TArray<AActor*> OutActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Controller->GetPawn());
	float Radius = 350.0f;
	FVector Center = Controller->GetPawn()->GetActorLocation();
	DrawDebugSphere(GetWorld(),Center,Radius,24,FColor::Green,false,2.0f,0,2.0f);
	bool bFoundActors = UKismetSystemLibrary::SphereOverlapActors(GetWorld(),Center,Radius,ObjectTypes,ACharacter::StaticClass(), IgnoreActors,OutActors);

	if (bFoundActors)
	{
		for (AActor* Actor : OutActors)
		{
			if (Actor == m_PlayerCharacter)
			{
				
				return true;
			}
		}
	}
	return false;
}
