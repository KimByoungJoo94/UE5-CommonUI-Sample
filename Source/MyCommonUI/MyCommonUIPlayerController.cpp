// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyCommonUIPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "MyCommonUI.h"
#include "UI/MCRootLayout.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "Widgets/Input/SVirtualJoystick.h"

void AMyCommonUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (IsLocalPlayerController() && ShouldUseTouchControls())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogMyCommonUI, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}

	/* MC 기본 템플릿과 구분 */
	InitializeRootLayout();
	/* ~MC */
}

void AMyCommonUIPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}

		/* MC 기본 템플릿과 구분 */
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			EnhancedInputComponent->BindAction(ControllerInputData.OpenSettingAction, ETriggerEvent::Started, this, &ThisClass::OnOpenSettingActionStarted);
		}
		/* ~MC */
	}
}

bool AMyCommonUIPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

/* MC 기본 템플릿과 구분 */
void AMyCommonUIPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();

	const UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (UEnhancedInputUserSettings* UserSettings = InputSubsystem->GetUserSettings())
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			if (CurrentContext != nullptr)
			{
				UserSettings->RegisterInputMappingContext(CurrentContext);
			}
		}
	}
}

void AMyCommonUIPlayerController::InitializeRootLayout()
{
	if (IsLocalPlayerController() && RootLayoutClass.Get())
	{
		RootLayout = CreateWidget<UMCRootLayout>(this, RootLayoutClass);
		if (RootLayout)
		{
			RootLayout->AddToPlayerScreen();
		}
	}
}

void AMyCommonUIPlayerController::OnOpenSettingActionStarted()
{
	if (RootLayout)
	{
		RootLayout->OpenSettingsScreen();
	}
}
/* ~MC */
