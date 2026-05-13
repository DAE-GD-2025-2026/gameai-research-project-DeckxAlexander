// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackPlayerAction.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIResearch/GOAPAIController.h"
#include "AIResearch/MainGamemode.h"
#include "AIResearch/ProjectileActor.h"

void UAttackPlayerAction::OnProjectileHit(AActor* OtherActor)
{
	if (OtherActor == m_PlayerCharacter)
	{
		m_Controller->ProcessSuccess();
		AMainGamemode* gamemode = Cast<AMainGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
		gamemode->SetWorldState(m_Effects);
		m_PlayerCharacter->Destroy();
	}
	else m_Controller->ProcessFailure();
}

void UAttackPlayerAction::OnProjectileFail()
{
	
	m_Controller->ProcessFailure();
	
}

void UAttackPlayerAction::Start(AGOAPAIController* Controller)
{
	Super::Start(Controller);

	m_PlayerCharacter = UGameplayStatics::GetPlayerPawn(Controller->GetWorld(), 0);
	m_Controller = Controller;

	FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(Controller->GetPawn()->GetActorLocation(),m_PlayerCharacter->GetActorLocation());

	Controller->GetPawn()->SetActorRotation(LookAt);
	
	FVector SpawnLocation = Controller->GetPawn()->GetActorLocation();
	FRotator SpawnRotation = Controller->GetPawn()->GetActorRotation();


	FActorSpawnParameters Params;
	Params.Owner = Controller->GetPawn();
	Params.Instigator = Controller->GetPawn()->GetInstigator();
	
	SpawnLocation += Controller->GetPawn()->GetActorForwardVector() * 200.f;
	
	AProjectileActor* Projectile = GetWorld()->SpawnActor<AProjectileActor>(Controller->ProjectileClass,SpawnLocation,SpawnRotation,Params);
	Projectile->SetOwner(Controller->GetPawn());
	Projectile->Init(this);
	
	
	
	
}

void UAttackPlayerAction::Tick(AGOAPAIController* Controller, float DeltaTime)
{
	Super::Tick(Controller, DeltaTime);
}
