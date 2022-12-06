// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RollerBallPlayer.generated.h"

//#include "Camera/CameraComponent.h"
//#include "GameFramework/SpringArmComponent.h"

//forward declaration
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ROLLERBALL_API ARollerBallPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARollerBallPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Define Components using property specifiers
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* Camera;
	
	//variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveForce = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpImpulse = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxJumpCount = 1;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override; not needed

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//functions
	void MoveRight(float Value);
	void MoveForward(float Value);
	void Jump();
	
	int32 JumpCount = 0;
};
