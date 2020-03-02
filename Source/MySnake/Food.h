// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Food.generated.h"

class USphereComponent;
class UStaticMesh;

UCLASS()
class MYSNAKE_API AFood : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	USphereComponent* MyRootComponent;

	UStaticMesh* SnakeEeatMesh;

	void CollectEat();

	float StepDelay = 5.0f;

	float BuferTime = 0;
};
 