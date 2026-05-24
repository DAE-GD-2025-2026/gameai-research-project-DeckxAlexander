// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentCharacter.h"
#include "GOAPAIController.h"
#include "PlayerCharacter.h"
#include "Actions/RoamAction.h"

// Sets default values
AAgentCharacter::AAgentCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 4000.f;
	PawnSensing->SetPeripheralVisionAngle(60.f);
	
	AlertConditions.Add(FName("Alerted"), false);
}

// Called when the game starts or when spawned
void AAgentCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(
			this,
			&AAgentCharacter::OnPawnSeen);
	}
}

void AAgentCharacter::OnPawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn)
		return;


	if (SeenPawn->IsA(APlayerCharacter::StaticClass()))
	{
		if (AGOAPAIController* AIController =
			Cast<AGOAPAIController>(GetController()))
		{
			for (auto state : AlertConditions)
			{
				const auto* key = AIController->GetCurrentState().Find(state.Key);
				if (key != nullptr && *key == state.Value )
				{
					//AIController->StopMovement();
					AIController->SetState({{FName("Alerted"), true}});
					AIController->SetGoalState({{FName("Alarm"), true}});
				}
			}


		}
	}
}

// Called every frame
void AAgentCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAgentCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

