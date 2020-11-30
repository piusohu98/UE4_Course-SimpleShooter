// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(SceneRoot);
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
		
	APawn* PlayerPawn = Cast<APawn>(GetOwner());
	if (PlayerPawn != nullptr)
	{		
		AController* OwnerController = PlayerPawn->GetController();
		if (OwnerController != nullptr)
		{
			FVector Location;
			FRotator Rotation;
			OwnerController->GetPlayerViewPoint(Location, Rotation);
			FVector End = Location + Rotation.Vector() * MaxRange;
			FHitResult Hit;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);
			Params.AddIgnoredActor(GetOwner());
			bool hasHit = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
			if (hasHit)
			{
				// DrawDebugPoint(GetWorld(), Hit.Location, 15.f, FColor::Red, true);
				if (HitExplosion != nullptr)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitExplosion, Hit.Location, Rotation * 180, true);

					AActor* HitActor = Hit.GetActor();
					if (HitActor != nullptr)
					{
						FVector HitDirection = -Rotation.Vector();
						FPointDamageEvent DamageEvent(Damage, Hit, HitDirection, nullptr);
						HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
					}
				}				
			}
		}		
	}
}

