#include "SnakePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "SnakePawn.h"
#include "Definitions.h"
#include "Kismet/GameplayStatics.h"

void ASnakePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASnakePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Log, TEXT("ASnakePlayerController::OnPossess"));

	SnakePawn = Cast<ASnakePawn>(GetPawn());

	if (!IsValid(SnakePawn))
	{
		UE_LOG(LogTemp, Error, TEXT("ASnakePlayerController::OnPossess -> SnakePawn not valid!"));
		return;
	}

	SnakePlayerState = Cast<ASnakePlayerState>(PlayerState);

	if (!IsValid(SnakePlayerState))
	{
		UE_LOG(LogTemp, Error, TEXT("ASnakePlayerController::OnPossess -> SnakePlayerState not valid!"));
		return;
	}

	InitializeInput();
}

void ASnakePlayerController::InitializeInput()
{
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!IsValid(SubSystem))
	{
		UE_LOG(LogTemp, Error, TEXT("ASnakePlayerController::InitializeInput -> Invalid Subsystem"));
		return;
	}

	SubSystem->ClearAllMappings();

	if (SnakePlayerState && Keyboard1MappingContext)
	{
		SubSystem->AddMappingContext(Keyboard1MappingContext, 0);
		UE_LOG(LogTemp, Log, TEXT("Added Keyboard1MappingContext"));
	}
}

void ASnakePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	if (!IsValid(Input))
	{
		UE_LOG(LogTemp, Error, TEXT("ASnakePlayerController::SetupInputComponent -> Input not set!"));
		return;
	}

	// Check that all keyboard actions are set
	if (!IsValid(KB1UpAction) || !IsValid(KB1DownAction) || !IsValid(KB1LeftAction) || !IsValid(KB1RightAction))
	{
		UE_LOG(LogTemp, Error, TEXT("ASnakePlayerController::SetupInputComponent -> KB1 Actions not set!"));
		return;
	}

	if (!IsValid(KB2UpAction) || !IsValid(KB2DownAction) || !IsValid(KB2LeftAction) || !IsValid(KB2RightAction))
	{
		UE_LOG(LogTemp, Error, TEXT("ASnakePlayerController::SetupInputComponent -> KB2 Actions not set!"));
		return;
	}

	// Bind Keyboard 1 actions (WASD)
	Input->BindAction(KB1UpAction, ETriggerEvent::Triggered, this, &ASnakePlayerController::KB1UpEvent);
	Input->BindAction(KB1DownAction, ETriggerEvent::Triggered, this, &ASnakePlayerController::KB1DownEvent);
	Input->BindAction(KB1LeftAction, ETriggerEvent::Triggered, this, &ASnakePlayerController::KB1LeftEvent);
	Input->BindAction(KB1RightAction, ETriggerEvent::Triggered, this, &ASnakePlayerController::KB1RightEvent);

	// Bind Keyboard 2 actions (Arrow keys)
	Input->BindAction(KB2UpAction, ETriggerEvent::Triggered, this, &ASnakePlayerController::KB2UpEvent);
	Input->BindAction(KB2DownAction, ETriggerEvent::Triggered, this, &ASnakePlayerController::KB2DownEvent);
	Input->BindAction(KB2LeftAction, ETriggerEvent::Triggered, this, &ASnakePlayerController::KB2LeftEvent);
	Input->BindAction(KB2RightAction, ETriggerEvent::Triggered, this, &ASnakePlayerController::KB2RightEvent);

	UE_LOG(LogTemp, Log, TEXT("ASnakePlayerController::SetupInputComponent -> All inputs bound successfully"));
}

ASnakePawn* ASnakePlayerController::GetPawnUsingKeyboard(int32 KeyboardId)
{
	if (SnakePlayerState)
	{
		ESnakeControllerType ControllerType = SnakePlayerState->GetSnakeControllerType();
		
		if ((KeyboardId == 1 && ControllerType == ESnakeControllerType::Keyboard1) ||
		    (KeyboardId == 2 && ControllerType == ESnakeControllerType::Keyboard2))
		{
			return SnakePawn;
		}
	}
	
	TArray<AActor*> Controllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASnakePlayerController::StaticClass(), Controllers);

	for (AActor* Actor : Controllers)
	{
		ASnakePlayerController* OtherController = Cast<ASnakePlayerController>(Actor);
		if (OtherController && OtherController->SnakePlayerState)
		{
			ESnakeControllerType OtherType = OtherController->SnakePlayerState->GetSnakeControllerType();

			if ((OtherType == ESnakeControllerType::Keyboard1 && KeyboardId == 1) ||
			    (OtherType == ESnakeControllerType::Keyboard2 && KeyboardId == 2))
			{
				return OtherController->SnakePawn;
			}
		}
	}

	return nullptr;
}

// Keyboard 1 event handlers (WASD)
void ASnakePlayerController::KB1UpEvent(const FInputActionValue& Value)
{
	if (ASnakePawn* UseSnakePawn = GetPawnUsingKeyboard(1))
	{
		UseSnakePawn->AddDirectionToQueue(ESnakeDirection::Up);
	}
}

void ASnakePlayerController::KB1DownEvent(const FInputActionValue& Value)
{
	if (ASnakePawn* UseSnakePawn = GetPawnUsingKeyboard(1))
	{
		UseSnakePawn->AddDirectionToQueue(ESnakeDirection::Down);
	}
}

void ASnakePlayerController::KB1LeftEvent(const FInputActionValue& Value)
{
	if (ASnakePawn* UseSnakePawn = GetPawnUsingKeyboard(1))
	{
		UseSnakePawn->AddDirectionToQueue(ESnakeDirection::Left);
	}
}

void ASnakePlayerController::KB1RightEvent(const FInputActionValue& Value)
{
	if (ASnakePawn* UseSnakePawn = GetPawnUsingKeyboard(1))
	{
		UseSnakePawn->AddDirectionToQueue(ESnakeDirection::Right);
	}
}

// Keyboard 2 event handlers (Arrow keys)
void ASnakePlayerController::KB2UpEvent(const FInputActionValue& Value)
{
	if (ASnakePawn* UseSnakePawn = GetPawnUsingKeyboard(2))
	{
		UseSnakePawn->AddDirectionToQueue(ESnakeDirection::Up);
	}
}

void ASnakePlayerController::KB2DownEvent(const FInputActionValue& Value)
{
	if (ASnakePawn* UseSnakePawn = GetPawnUsingKeyboard(2))
	{
		UseSnakePawn->AddDirectionToQueue(ESnakeDirection::Down);
	}
}

void ASnakePlayerController::KB2LeftEvent(const FInputActionValue& Value)
{
	if (ASnakePawn* UseSnakePawn = GetPawnUsingKeyboard(2))
	{
		UseSnakePawn->AddDirectionToQueue(ESnakeDirection::Left);
	}
}

void ASnakePlayerController::KB2RightEvent(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("KB2RightEvent"));
	if (ASnakePawn* UseSnakePawn = GetPawnUsingKeyboard(2))
	{
		UseSnakePawn->AddDirectionToQueue(ESnakeDirection::Right);
	}
}
