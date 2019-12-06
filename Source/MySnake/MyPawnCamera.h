// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawnCamera.generated.h"

class UBoxComponent;
class UCameraComponent;
class USpringArmComponent;
class AMySnakeActor;

UCLASS()
class MYSNAKE_API AMyPawnCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawnCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UBoxComponent* MyRootComponent;

	// Камера персонажа
	UPROPERTY(EditAnywhere, Category = "Pawn")
	UCameraComponent* CameraComp;

	// SpringArm для камеры
	UPROPERTY(EditAnywhere, Category = "Pawn")
	USpringArmComponent* SpringArmComp;

	AMySnakeActor* MySnakePlayer;

	UFUNCTION(BlueprintCallable, Category = "SnakePawn")
	void AddSnakeToMap();

	void FMove(float ButtonVal);

	FVector2D WASD;

	float MinY = -1500.f;
	float MaxY = 1500.f;
	float MinX = -800.f;
	float MaxX = 800.f;

	float SpawnZ = 50.f;

	void AddRandomApple();

	float StepDelay = 1.f;

	float BuferTime = 0;

	int32 GameMode = 0;

	UFUNCTION(BlueprintCallable, Category = "SnakePawn")
	int32 GetGameMode() const { return GameMode; }

	UFUNCTION(BlueprintCallable, Category = "SnakePawn")
	int32 GetScore();

	bool GamePause = false;

	UFUNCTION(BlueprintCallable, Category = "SnakePawn")
	bool GetGamePause() const { return GamePause; }

	void SnakeDestroy();
};
   