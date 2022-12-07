// Fill out your copyright notice in the Description page of Project Settings.


#include "RollerBallGameModeBase.h"

#include "RollerBallItem.h"
#include "RollerBallWidget.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void ARollerBallGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollerBallItem::StaticClass(), Items);
	ItemsInLevel = Items.Num();

	if(GameWidgetClass)
	{
		GameWidget = Cast<URollerBallWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if(GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void ARollerBallGameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}

void ARollerBallGameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}
