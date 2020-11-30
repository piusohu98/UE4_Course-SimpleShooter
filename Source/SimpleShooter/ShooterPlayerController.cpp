// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    
    GetWorldTimerManager().SetTimer(RestartTimer, this, &AShooterPlayerController::RestartLevel, RestartDelay);
}