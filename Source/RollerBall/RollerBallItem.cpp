// Fill out your copyright notice in the Description page of Project Settings.


#include "RollerBallItem.h"

#include "RollerBallPlayer.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARollerBallItem::ARollerBallItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//create component because actors wont exist before this as they are only defined
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ARollerBallItem::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARollerBallItem::OverlapBegin);
}

void ARollerBallItem::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<ARollerBallPlayer>(OtherActor) != nullptr)
	{
		Collected();
	}
}

void ARollerBallItem::Collected_Implementation()
{
	//do gamemode stuffs
}

// Called every frame
//void ARollerBallItem::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}

