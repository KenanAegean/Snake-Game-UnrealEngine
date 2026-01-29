#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SnakePlayerState.h"
#include "SnakePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ASnakePawn;
struct FInputActionValue;

UCLASS()
class SNAKEGAME_API ASnakePlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void InitializeInput();
	
	UFUNCTION()
	ASnakePawn* GetPawnUsingKeyboard(int32 KeyboardId);

	UPROPERTY()
	TObjectPtr<ASnakePawn> SnakePawn;

	UPROPERTY()
	TObjectPtr<ASnakePlayerState> SnakePlayerState;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> Keyboard1MappingContext;

	// Keyboard 1 actions (WASD)
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> KB1UpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> KB1DownAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> KB1LeftAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> KB1RightAction;

	// Keyboard 2 actions (Arrow keys)
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> KB2UpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> KB2DownAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> KB2LeftAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> KB2RightAction;

	// Keyboard 1 event handlers
	UFUNCTION()
	void KB1UpEvent(const FInputActionValue& Value);

	UFUNCTION()
	void KB1DownEvent(const FInputActionValue& Value);

	UFUNCTION()
	void KB1LeftEvent(const FInputActionValue& Value);

	UFUNCTION()
	void KB1RightEvent(const FInputActionValue& Value);

	// Keyboard 2 event handlers
	UFUNCTION()
	void KB2UpEvent(const FInputActionValue& Value);

	UFUNCTION()
	void KB2DownEvent(const FInputActionValue& Value);

	UFUNCTION()
	void KB2LeftEvent(const FInputActionValue& Value);

	UFUNCTION()
	void KB2RightEvent(const FInputActionValue& Value);
};
