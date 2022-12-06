// Fill out your copyright notice in the Description page of Project Settings.


#include "RollerBallGameModeBase.h"

#include "RollerBallItem.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void ARollerBallGameModeBase::BeginPlay()
{
	//Super::BeginPlay();

	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollerBallItem::StaticClass(), Items);
	ItemsInLevel = Items.Num();
}

void ARollerBallGameModeBase::UpdateItemText()
{
	
}

void ARollerBallGameModeBase::ItemCollected()
{
	ItemsCollected++;
}
