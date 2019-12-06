// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawnCamera.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MySnake.h"
#include "MySnakeActor.h"
#include "Components/InputComponent.h"
#include "Food.h"

// Sets default values
AMyPawnCamera::AMyPawnCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MyRootComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));

	RootComponent = MyRootComponent;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 0));
	SpringArmComp->SetRelativeRotation(FRotator(-90.f, 0, 0));
	SpringArmComp->TargetArmLength = 1700.0f;
	SpringArmComp->bDoCollisionTest = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);


	/*
	//корневой компонент для камеры
	MyRootComponent = CreateDefaultSubobject<UBoxComponent>("RootModel");
	//блок к пешке
	RootComponent = MyRootComponent;

	//создание штатива для камеры
	CameraSpring = CreateDefaultSubobject<USpringArmComponent>("Spring");
	//устанавливаем позицию штатива
	CameraSpring->SetRelativeLocation(FVector(0,0,0));
	//прикрепляем его к камере
	CameraSpring->AttachTo(MyRootComponent);

	//создание камеры
	MyCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	//прикрепляем камеру к SpringArm
	MyCamera->AttachTo(CameraSpring, USpringArmComponent::SocketName);
	*/
}  

// Called when the game starts or when spawned
void AMyPawnCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawnCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameMode > 0)
	{
		BuferTime += DeltaTime;
		if (BuferTime > StepDelay)
		{
			if (!GamePause) AddRandomApple();

			BuferTime = 0;
		}
	}
	
}

// Called to bind functionality to input
void AMyPawnCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Move", this, &AMyPawnCamera::FMove);
}

void AMyPawnCamera::AddSnakeToMap()
{
	FVector StartPoint = GetActorLocation();

	FRotator StartPointRotation = GetActorRotation();

	if (GetWorld())
	{
		MySnakePlayer = GetWorld()->SpawnActor<AMySnakeActor>(StartPoint, StartPointRotation);
		GameMode = 1;
		MySnakePlayer->WhoPawn = this;
	}
}

void AMyPawnCamera::FMove(float ButtonVal)
{
	int32 Key = ButtonVal;

	if (GameMode > 0)
	{
		if (Key == 5)
		{
			GamePause = !GamePause;
		}

		if (!GamePause)
		{
			switch (Key)
			{
			case 1:
				if (WASD.X != 1)
				{
					WASD = FVector2D(0, 0);
					WASD.X = -1;
				}
				break;

			case 2:
				if (WASD.X != -1)
				{
					WASD = FVector2D(0, 0);
					WASD.X = 1;
				}
				break;

			case 3:
				if (WASD.Y != -1)
				{
					WASD = FVector2D(0, 0);
					WASD.Y = 1;
				}
				break;

			case 4:
				if (WASD.Y != 1)
				{
					WASD = FVector2D(0, 0);
					WASD.Y = -1;
				}
				break;
			}

			if (MySnakePlayer)
			{
				MySnakePlayer->DirectionMoveSnake = WASD;
			}
		}
		else
		{
			MySnakePlayer->DirectionMoveSnake = FVector2D(0, 0);
		}
	}
}

void AMyPawnCamera::AddRandomApple()
{
	FRotator StartPointRotation = FRotator(0, 0, 0);

	float SpawnX = FMath::FRandRange(MinX, MaxX);

	float SpawnY = FMath::FRandRange(MinY, MaxY);

	FVector StartPoint = FVector(SpawnX, SpawnY, SpawnZ);

	if (MySnakePlayer)
	{
		if (GetWorld())
		{
			GetWorld()->SpawnActor<AFood>(StartPoint, StartPointRotation);
		}
	}
}

int32 AMyPawnCamera::GetScore()
{
	if (MySnakePlayer)
	{
		return MySnakePlayer->Score;
	}
	return 0; 
}

void AMyPawnCamera::SnakeDestroy()
{
	GameMode = 0;

	if (MySnakePlayer) MySnakePlayer->Destroy(true, true);
}

 