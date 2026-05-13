// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GOAPAction.h"
#include "Actions/AttackPlayerAction.h"
// Sets default values
AProjectileActor::AProjectileActor()
{
	
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;

	
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collision->SetCollisionObjectType(ECC_WorldDynamic);

	Collision->SetCollisionResponseToAllChannels(ECR_Block);

	Collision->SetNotifyRigidBodyCollision(true);
	
	Collision->SetNotifyRigidBodyCollision(true);
	Collision->SetGenerateOverlapEvents(true);
	
	Collision->IgnoreActorWhenMoving(GetOwner(), true);


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	ProjectileMovement->ProjectileGravityScale = 0.f;

}

void AProjectileActor::Init(UAttackPlayerAction* Action)
{
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->Velocity =GetActorForwardVector() * ProjectileMovement->InitialSpeed;
	
	
	m_GOAPAction = Action;
}



// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentHit.AddDynamic(this, &AProjectileActor::HandleHit);
	OnDestroyed.AddDynamic(this, &AProjectileActor::HandleDestroyed);
	SetLifeSpan(2.0f);
}

void AProjectileActor::HandleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if ( OtherActor == GetOwner() ) return;
	if (IsValid(m_GOAPAction) ) m_GOAPAction->OnProjectileHit(OtherActor);
	
	
	
	
	m_hasHit = true;
	Destroy();
}

void AProjectileActor::HandleDestroyed(AActor* DestroyedActor)
{
	if (m_hasHit) return;
	m_GOAPAction->OnProjectileFail();
	
}

// Called every frame


