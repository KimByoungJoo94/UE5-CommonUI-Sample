#include "UI/List/MCSettingListItem.h"
#include "CommonTextBlock.h"
#include "CommonInputBaseTypes.h"
#include "CommonInputSubsystem.h"
#include "Components/Button.h"
#include "DataTable/MCSettingTableRowData.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "UI/List/MCSettingListItemData.h"
#include "Subsystem/MCGameDataSubsystem.h"
#include "Components/InputKeySelector.h"
#include "Components/Image.h"
#include "Templates/UnrealTemplate.h"
#include "UserSettings/EnhancedInputUserSettings.h"

void UMCSettingListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SettingTableRowName = NAME_None;
	if (const UMCSettingListItemData* SettingListItemData = Cast<UMCSettingListItemData>(ListItemObject))
	{
		SettingTableRowName = SettingListItemData->RowHandle.RowName;
	}

	UpdateNameText();
	UpdateKey();
}

void UMCSettingListItem::NativeConstruct()
{
	Super::NativeConstruct();

	BindWidgetDelegate();

	if (DefaultFocusButton)
	{
		SetDesiredFocusWidget(DefaultFocusButton);
	}

	if (KeySelector)
	{
		SetNavigationRuleExplicit(EUINavigation::Right, KeySelector);

		KeySelector->SetNavigationRuleExplicit(EUINavigation::Left, DefaultFocusButton);
		KeySelector->SetNavigationRuleExplicit(EUINavigation::Right, DefaultFocusButton);
	}
}

void UMCSettingListItem::NativeDestruct()
{
	UnbindWidgetDelegate();

	Super::NativeDestruct();
}

void UMCSettingListItem::BindWidgetDelegate()
{
	if (KeySelector)
	{
		KeySelector->OnKeySelected.RemoveDynamic(this, &UMCSettingListItem::OnKeySelectorKeySelected);
		KeySelector->OnKeySelected.AddDynamic(this, &UMCSettingListItem::OnKeySelectorKeySelected);
	}
}

void UMCSettingListItem::UnbindWidgetDelegate()
{
	if (KeySelector)
	{
		KeySelector->OnKeySelected.RemoveDynamic(this, &UMCSettingListItem::OnKeySelectorKeySelected);
	}
}

void UMCSettingListItem::UpdateNameText()
{
	if (UMCGameDataSubsystem* GameDataSubsystem = UGameInstance::GetSubsystem<UMCGameDataSubsystem>(GetGameInstance()))
	{
		if (const FMCSettingTableRowData* SettingTableRowData = GameDataSubsystem->GetDataRow<FMCSettingTableRowData>(SettingTableRowName))
		{
			if (SettingNameText)
			{
				SettingNameText->SetText(SettingTableRowData->DisplayName);
			}
		}
	}
}

void UMCSettingListItem::UpdateKey()
{
	UMCGameDataSubsystem* GameDataSubsystem = UGameInstance::GetSubsystem<UMCGameDataSubsystem>(GetGameInstance());
	const FMCSettingTableRowData* SettingTableRowData = GameDataSubsystem ? GameDataSubsystem->GetDataRow<FMCSettingTableRowData>(SettingTableRowName) : nullptr;

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningLocalPlayer());
	UEnhancedInputUserSettings* UserSettings = InputSubsystem ? InputSubsystem->GetUserSettings() : nullptr;

	const FPlayerKeyMapping* KeyMapping = nullptr;
	if (SettingTableRowData && SettingTableRowData->InputMappingName.IsNone() == false && UserSettings)
	{
		KeyMapping = UserSettings->FindCurrentMappingForSlot(SettingTableRowData->InputMappingName, EPlayerMappableKeySlot::First);
	}

	const FKey DefaultKey = KeyMapping ? KeyMapping->GetDefaultKey() : EKeys::Invalid;
	const FKey UserKey = KeyMapping && KeyMapping->IsCustomized() ? KeyMapping->GetCurrentKey() : EKeys::Invalid;

	UpdateKeyIconText(DefaultKey, UserKey);
}

void UMCSettingListItem::UpdateKeyIconText(const FKey& InDefaultKey, const FKey& InUserKey)
{
	const bool bIsGamepadKey = InDefaultKey.IsGamepadKey();
	if (KeySelector)
	{
		const TGuardValue<bool> UpdatingKeySelector(bUpdatingKeySelector, true);
		KeySelector->SetIsEnabled(InDefaultKey.IsValid());
		KeySelector->SetAllowGamepadKeys(bIsGamepadKey);
		KeySelector->SetNoKeySpecifiedText(NSLOCTEXT("MCSettingListItem", "OverwriteKey", "\uB36E\uC5B4\uC4F0\uAE30"));
		KeySelector->SetSelectedKey(FInputChord(InUserKey));
	}

	if (KeyIcon == nullptr)
	{
		return;
	}

	const UCommonInputPlatformSettings* PlatformSettings = UCommonInputPlatformSettings::Get();
	const UCommonInputSubsystem* CommonInput = bIsGamepadKey ? UCommonInputSubsystem::Get(GetOwningLocalPlayer()) : nullptr;
	const ECommonInputType InputType = bIsGamepadKey ? ECommonInputType::Gamepad : ECommonInputType::MouseAndKeyboard;
	const FName GamepadName = CommonInput ? CommonInput->GetCurrentGamepadName() : NAME_None;

	FSlateBrush KeyBrush;
	const bool bHasIcon = InDefaultKey.IsValid() && PlatformSettings && PlatformSettings->TryGetInputBrush(KeyBrush, InDefaultKey, InputType, GamepadName);

	KeyIcon->SetBrush(KeyBrush);
	KeyIcon->SetVisibility(bHasIcon ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
}

void UMCSettingListItem::OnKeySelectorKeySelected(FInputChord InSelectedKey)
{
	if (bUpdatingKeySelector)
	{
		return;
	}

	if (InSelectedKey.Key.IsValid() == false)
	{
		UpdateKey();
		return;
	}

	UMCGameDataSubsystem* GameDataSubsystem = UGameInstance::GetSubsystem<UMCGameDataSubsystem>(GetGameInstance());
	if (GameDataSubsystem == nullptr)
	{
		return;
	}

	const FMCSettingTableRowData* SettingTableRowData = GameDataSubsystem->GetDataRow<FMCSettingTableRowData>(SettingTableRowName);
	if (SettingTableRowData == nullptr)
	{
		return;
	}

	const UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningLocalPlayer());
	UEnhancedInputUserSettings* UserSettings = InputSubsystem != nullptr ? InputSubsystem->GetUserSettings() : nullptr;

	if (UserSettings == nullptr)
	{
		return;
	}

	FKey NewKey = InSelectedKey.Key;
	const bool bIsGamepadRow = SettingTableRowData->Type == EMCSettingType::Gamepad;

	if (bIsGamepadRow && NewKey == EKeys::LeftMouseButton)
	{
		if (const UCommonInputSubsystem* CommonInput = UCommonInputSubsystem::Get(GetOwningLocalPlayer()))
		{
			if (CommonInput->GetIsGamepadSimulatedClick())
			{
				NewKey = EKeys::Virtual_Gamepad_Accept.GetVirtualKey();
			}
		}
	}

	if (NewKey.IsGamepadKey() != bIsGamepadRow)
	{
		UpdateKey();
		return;
	}

	FMapPlayerKeyArgs Args;
	Args.MappingName = SettingTableRowData->InputMappingName;
	Args.Slot = EPlayerMappableKeySlot::First;
	Args.NewKey = NewKey;
	Args.bCreateMatchingSlotIfNeeded = false;

	FGameplayTagContainer FailureReason;
	UserSettings->MapPlayerKey(Args, FailureReason);

	if (FailureReason.IsEmpty() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("키 변경 실패 [%s]: %s"), *Args.MappingName.ToString(), *FailureReason.ToString());
		UpdateKey();
		return;
	}

	UpdateKey();
	UserSettings->AsyncSaveSettings();
}
