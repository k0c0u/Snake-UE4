// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DethActor.generated.h"

class UBoxComponent;
class UMaterialInstance;

UCLASS()
class MYSNAKE_API ADethActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADethActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UBoxComponent* MyRootComponent;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* WallColor;

	void CollideWall();
};
