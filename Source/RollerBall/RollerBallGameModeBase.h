// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollerBallGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ROLLERBALL_API ARollerBallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	int32 ItemsCollected = 0;
	int32 ItemsInLevel = 0;

	//widget variables

	virtual void BeginPlay() override;

	void UpdateItemText();

public:

	void ItemCollected();
	
};
