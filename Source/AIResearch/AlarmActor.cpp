// Fill out your copyright notice in the Description page of Project Settings.


#include "AlarmActor.h"

#include "GOAPAIController.h"
#include "MainGamemode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAlarmActor::AAlarmActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAlarmActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAlarmActor::SoundAlarm()
{
	auto GM = Cast<AMainGamemode>(UGameplayStatics::GetGameMode(this));
	GM->SetWorldState({{FName("Alarm"), true}});
	
	TArray<AActor*> actors{};
	UGameplayStatics::GetAllActorsOfClass(this, AGOAPAIController::StaticClass(), actors);
	
	for (AActor* actor : actors)
	{
		auto controller = Cast<AGOAPAIController>(actor);
		controller->SetGoalState({{FName("PAlive"), false}});
		
	}
	
	
}

// Called every frame


