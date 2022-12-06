// Fill out your copyright notice in the Description page of Project Settings.


#include "RollerBallPlayer.h"

//include declaration (costly and more power because calling functions)
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARollerBallPlayer::ARollerBallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//creating components so they exist on the actors
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	//setting root component to be mesh (default)
	RootComponent = Mesh;
	//attaching springarm to mesh so it only follows mesh transform
	SpringArm->SetupAttachment(Mesh);
	//attaching the camera to springarm so camera will follow springarm transform
	Camera->SetupAttachment(SpringArm);

	//set physics to true
	Mesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ARollerBallPlayer::BeginPlay()
{
	Super::BeginPlay();

	//account for mass in MoveForce
	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();

	Mesh->OnComponentHit.AddDynamic(this, &ARollerBallPlayer::OnHit);
}

// Called every frame
//void ARollerBallPlayer::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}

// Called to bind functionality to input
void ARollerBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//custom input axis binding
	InputComponent->BindAxis("MoveForward", this, &ARollerBallPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARollerBallPlayer::MoveRight);
	//custom action binding
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollerBallPlayer::Jump);
}

void ARollerBallPlayer::MoveRight(float Value)
{
	//move character based on input and MoveForce
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ARollerBallPlayer::MoveForward(float Value)
{
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Forward);
}

void ARollerBallPlayer::Jump()
{
	//limit the number of jumps we can make
	if(JumpCount >= MaxJumpCount){return;}
	//apply an impulse to the mesh in z axis
	Mesh->AddImpulse(FVector(0,0, JumpImpulse));
	//track jump times
	JumpCount++;
}

void ARollerBallPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	//get direction we hit the surface on z axis
	const float HitDirection = Hit.Normal.Z;

	//GEngine->AddOnScreenDebugMessage(-1,0.1f,FColor::Orange,FString::Printf(TEXT("%f"), HitDirection));
	//UE_LOG() output goes to console
	
	//If it is more than 0 then we have hit something below us. 1 is flat, anything between is a slope.
	if(HitDirection > 0)
	{
		JumpCount = 0;
	}
}

//:: -> . Operators