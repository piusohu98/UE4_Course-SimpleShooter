// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

AShooterAIController::AShooterAIController()
{

}

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        APawn* AIPawn = GetPawn();
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), AIPawn->GetActorLocation());

        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
    }

    /*
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn != nullptr)
    {
        SetFocus(PlayerPawn, EAIFocusPriority::Gameplay);
    }
    */
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    /*
    if (PlayerPawn != nullptr)
    {
        bool FollowPlayer = true;
        if (GetPawn<AShooterCharacter>()->IsDead())
        {
            FollowPlayer = false;
        }
        else
        {
            FVector Location;
            FRotator Rotation;
            GetPlayerViewPoint(Location, Rotation);
            if (LineOfSightTo(PlayerPawn, Location))
            {
                MoveToActor(PlayerPawn, AcceptanceRadius);
            }
            else
            {
                FollowPlayer = false;
            }            
        }

        if (!FollowPlayer)
        {
            StopMovement();
            ClearFocus(EAIFocusPriority::Gameplay);
        }
    }
    */

}