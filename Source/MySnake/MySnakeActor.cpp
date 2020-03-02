// Fill out your copyright notice in the Description page of Project Settings.


#include "MySnakeActor.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "MyPawnCamera.h"



// Sets default values
AMySnakeActor::AMySnakeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SnakeSize = 15;

	StepSnake = 45.0f;
	
	FVector Posa = GetActorLocation();

	MyRootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Myroot"));
	MyRootComponent->SetRelativeLocation(Posa);

	RootComponent = MyRootComponent;

	CreateSnakeBody();

}

// Called when the game starts or when spawned
void AMySnakeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMySnakeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetVisibleChank();

	BuferTime += DeltaTime;
	if (BuferTime > StepDelay)
	{
		MoveSnake();

		BuferTime = 0;
	}

	//SelfEating();
}

void AMySnakeActor::CreateSnakeBody()
{
	class UStaticMesh* SnakeChankMesh;
	SnakeChankMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Sphere")).Object;

	class UMaterialInstance* BodyColor;
	BodyColor = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/Snake/Material/Instance/M_Tech_Hex_Tile_Inst.M_Tech_Hex_Tile_Inst'")).Get();

	class UMaterialInstance* WormHead;
	WormHead = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/Snake/Material/Instance/M_Tech_Hex_Tile_Pulse_Inst.M_Tech_Hex_Tile_Pulse_Inst'")).Get();

	FVector NextPoint = GetActorLocation();

	FName NameChank;

	FString TheString;

	for (int32 i = 0; i < SnakeSize; i++)
	{
		TheString = "Chanks" + FString::FromInt(i);

		NameChank = FName(*TheString);

		class UStaticMeshComponent* BodyChank = CreateDefaultSubobject<UStaticMeshComponent>(NameChank);
		BodyChank->SetStaticMesh(SnakeChankMesh);
		BodyChank->SetRelativeLocation(NextPoint);

		SnakeBody.Add(BodyChank);

		NextPoint.X -= StepSnake;

		BodyChank->AttachTo(MyRootComponent);

		BodyChank->SetMaterial(0, BodyColor);

		if (i == 0)
		{
			BodyChank->SetMaterial(0, WormHead);
		}
		else
		{
			BodyChank->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
 	}

	SetVisibleChank();
}

void AMySnakeActor::SetVisibleChank()
{
	for (int32 IndexShow = 0; IndexShow < SnakeBody.Num(); IndexShow++)
	{
		if (IndexShow < VisibleBodyChank)
		{
			SnakeBody[IndexShow]->SetVisibility(true, true);
		}
		else
		{
			SnakeBody[IndexShow]->SetVisibility(false, true);
		}
	}
}

void AMySnakeActor::MoveSnake()
{
	if ((DirectionMoveSnake.X != 0) || (DirectionMoveSnake.Y != 0))
	{
		for (int Chank = SnakeBody.Num() - 1; Chank > 0; Chank--)
		{
			FVector V = SnakeBody[Chank - 1]->RelativeLocation;
			SnakeBody[Chank]->SetRelativeLocation(V);
		}
		
		FVector StartPoint = SnakeBody[0]->RelativeLocation;
		if (DirectionMoveSnake.X > 0) StartPoint.X -= StepSnake;
		if (DirectionMoveSnake.X < 0) StartPoint.X += StepSnake;

		if (DirectionMoveSnake.Y > 0) StartPoint.Y += StepSnake;
		if (DirectionMoveSnake.Y < 0) StartPoint.Y -= StepSnake;

		SnakeBody[0]->SetRelativeLocation(StartPoint);
	}
}

void AMySnakeActor::HaveDamage()
{
	WhoPawn->SnakeDestroy();
}

//void AMySnakeActor::SelfEating()
//{
//	bool Eating = SnakeBody[0]->OnComponentBeginOverlap.AddDynamic(this, SnakeBody);
//
//	if (Eating)
//	{
//		HaveDamage();
//	}
//}

