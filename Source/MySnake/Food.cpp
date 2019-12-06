// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "MySnakeActor.h"



// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootEeat"));
	RootComponent = MyRootComponent;
	
	SnakeEeatMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Sphere")).Object;

	class UMaterialInstance* EatColor;
	EatColor  = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/Snake/Material/Instance/M_Metal_Gold_Inst.M_Metal_Gold_Inst'")).Get();

	FVector Size = FVector(0.5f, 0.5f, 0.5f);

	class UStaticMeshComponent* EeatChank = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Eeat"));
	
	EeatChank->SetStaticMesh(SnakeEeatMesh);

	EeatChank->SetRelativeScale3D(Size);

	EeatChank->SetRelativeLocation(FVector(0, 0, 0));

	EeatChank->SetMaterial(0, EatColor);

	EeatChank->AttachTo(MyRootComponent);

	EeatChank->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	BuferTime += DeltaTime;

	if (BuferTime > StepDelay)
	{
		Destroy(true, true);
	}

	CollectEat();
}

void AFood::CollectEat()
{
	TArray<AActor*> CollectedActors; 

	GetOverlappingActors(CollectedActors);

	for (int32 i = 0; i < CollectedActors.Num(); ++i)
	{
		AMySnakeActor* const Test = Cast<AMySnakeActor>(CollectedActors[i]);

		if (Test)
		{
			Test->VisibleBodyChank++;

			Test->Score++;

			Destroy(true, true);

			break;
		}
	}
}

