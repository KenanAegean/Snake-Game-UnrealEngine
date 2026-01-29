#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SnakePlayerState.generated.h"

UENUM(BlueprintType)
enum class ESnakeControllerType : uint8
{
	Keyboard1 UMETA(DisplayName = "Keyboard 1 (WASD)"),
	Keyboard2 UMETA(DisplayName = "Keyboard 2 (Arrow Keys)"),
	AI        UMETA(DisplayName = "AI Controlled")
};

UCLASS()
class SNAKEGAME_API ASnakePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASnakePlayerState();

	UFUNCTION(BlueprintCallable, Category = "Snake")
	ESnakeControllerType GetSnakeControllerType() const { return SnakeControllerType; }

	UFUNCTION(BlueprintCallable, Category = "Snake")
	void SetSnakeControllerType(ESnakeControllerType NewType) { SnakeControllerType = NewType; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake")
	ESnakeControllerType SnakeControllerType = ESnakeControllerType::Keyboard1;
};
