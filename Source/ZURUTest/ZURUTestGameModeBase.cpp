// Fill out your copyright notice in the Description page of Project Settings.


#include "ZURUTestGameModeBase.h"

#include "MousePawn.h"

AZURUTestGameModeBase::AZURUTestGameModeBase(const FObjectInitializer& ObjectInitializer)
{
	DefaultPawnClass = AMousePawn::StaticClass();
}

void AZURUTestGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}