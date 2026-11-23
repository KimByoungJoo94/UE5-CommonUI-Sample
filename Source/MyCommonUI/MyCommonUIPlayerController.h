// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyCommonUIPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class UMCRootLayout;
class UUserWidget;

/* MC 기본 템플릿과 구분 */
USTRUCT()
struct FMCControllerInputData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> OpenSettingAction;
};
/* ~MC */

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS(abstract)
class AMyCommonUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** If true, the player will use UMG touch controls even if not playing on mobile platforms */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

protected:
	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	/** Returns true if the player should use UMG touch controls */
	bool ShouldUseTouchControls() const;

	/* MC 기본 템플릿과 구분 */
protected:
	virtual void ReceivedPlayer() override;

private:
	void InitializeRootLayout();
	
	void OnOpenSettingActionStarted();

private:
	UPROPERTY(Transient)
	TObjectPtr<UMCRootLayout> RootLayout;

	UPROPERTY(EditDefaultsOnly, Category = "MyCommonUI")
	TSubclassOf<UMCRootLayout> RootLayoutClass;

	UPROPERTY(EditDefaultsOnly, Category = "MyCommonUI")
	FMCControllerInputData ControllerInputData;	
	/* ~MC */
};
