#include "UI/Screen/MCScreenWidget.h"
#include "CommonAnimatedSwitcher.h"
#include "CommonButtonBase.h"
#include "CommonInputModeTypes.h"
#include "Components/HorizontalBox.h"
#include "Config/MCGameConfig.h"
#include "Engine/EngineBaseTypes.h"
#include "Groups/CommonButtonGroupBase.h"
#include "Input/CommonUIInputTypes.h"
#include "MyCommonUI.h"

UMCScreenWidget::UMCScreenWidget(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	bIsBackHandler = true;
}

TOptional<FUIInputConfig> UMCScreenWidget::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
}

void UMCScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (TabButtonContainer == nullptr || PanelSwitcher == nullptr)
	{
		return;
	}

	TArray<UCommonButtonBase*> TabButtonArray;
	for (UWidget* Child : TabButtonContainer->GetAllChildren())
	{
		if (UCommonButtonBase* TabButton = Cast<UCommonButtonBase>(Child))
		{
			TabButtonArray.Add(TabButton);
		}
	}

	const int32 PanelCount = PanelSwitcher->GetChildrenCount();
	if (TabButtonArray.IsEmpty() || TabButtonArray.Num() != PanelCount)
	{	
		UE_LOG(LogMyCommonUI, Warning, TEXT("TabButtonArray.IsEmpty() || TabButtonArray.Num() != PanelCount"));
		return;
	}

	TabButtonGroup = NewObject<UCommonButtonGroupBase>(this);
	for (UCommonButtonBase* TabButton : TabButtonArray)
	{
		TabButton->SetIsSelectable(true);
		TabButton->SetIsToggleable(false);
		TabButton->SetIsSelected(false, false);
		TabButtonGroup->AddWidget(TabButton);
	}

	TabButtonGroup->NativeOnSelectedButtonBaseChanged.AddUObject(this, &ThisClass::OnTabSelectionChanged);
	TabButtonGroup->SelectButtonAtIndex(0, false);
	TabButtonGroup->SetSelectionRequired(true);

	const UMCGameConfig* GameConfig = GetDefault<UMCGameConfig>();
	const FDataTableRowHandle& PreviousTabAction = GameConfig->GetPreviousTabAction();
	if (PreviousTabAction.IsNull() == false)
	{
		PreviousTabActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(PreviousTabAction, false, FSimpleDelegate::CreateUObject(this, &ThisClass::OnPreviousTabAction)));
	}

	const FDataTableRowHandle& NextTabAction = GameConfig->GetNextTabAction();
	if (NextTabAction.IsNull() == false)
	{
		NextTabActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(NextTabAction, false, FSimpleDelegate::CreateUObject(this, &ThisClass::OnNextTabAction)));
	}
}

void UMCScreenWidget::NativeDestruct()
{
	PreviousTabActionHandle.Unregister();
	NextTabActionHandle.Unregister();

	if (TabButtonGroup)
	{
		TabButtonGroup->NativeOnSelectedButtonBaseChanged.RemoveAll(this);
		TabButtonGroup->RemoveAll();
		TabButtonGroup = nullptr;
	}

	Super::NativeDestruct();
}

UWidget* UMCScreenWidget::NativeGetDesiredFocusTarget() const
{
	if (TabButtonGroup)
	{
		if (UCommonButtonBase* SelectedTab = TabButtonGroup->GetSelectedButtonBase())
		{
			return SelectedTab;
		}
	}

	return Super::NativeGetDesiredFocusTarget();
}

void UMCScreenWidget::OnTabSelectionChanged(UCommonButtonBase* InSelectedButton, int32 InTabIndex)
{
	if (InSelectedButton && PanelSwitcher && PanelSwitcher->GetChildAt(InTabIndex))
	{
		PanelSwitcher->SetActiveWidgetIndex(InTabIndex);
	}
}

void UMCScreenWidget::OnPreviousTabAction()
{
	if (TabButtonGroup)
	{
		TabButtonGroup->SelectPreviousButton();
	}
}

void UMCScreenWidget::OnNextTabAction()
{
	if (TabButtonGroup)
	{
		TabButtonGroup->SelectNextButton();
	}
}
