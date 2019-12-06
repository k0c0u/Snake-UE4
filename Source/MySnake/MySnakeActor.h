// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySnakeActor.generated.h"

class USphereComponent;
class AMyPawnCamera;

UCLASS()
class MYSNAKE_API AMySnakeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySnakeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Максимальная длинна змейки
	int32 SnakeSize;

	//Ширина шага змейки равна ширине одной части змейки
	float StepSnake;

	//Массив который будет хранить все части змейки
	TArray<UStaticMeshComponent*> SnakeBody;

	float StepDelay = 0.5f;

	float BuferTime = 0;


public:	

	UPROPERTY(EditAnywhere)
	FVector2D DirectionMoveSnake;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateSnakeBody();

	UPROPERTY(EditAnywhere)
	USphereComponent* MyRootComponent;

	UPROPERTY(EditAnywhere)
	int32 VisibleBodyChank = 3;

	void SetVisibleChank();

	void MoveSnake();

	int32 Score = 0;

	AMyPawnCamera* WhoPawn;

	void HaveDamage();
};
