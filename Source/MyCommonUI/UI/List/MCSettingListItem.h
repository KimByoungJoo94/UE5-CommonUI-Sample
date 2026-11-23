#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "CommonButtonBase.h"
#include "MCSettingListItem.generated.h"

class UButton;
class UCommonTextBlock;
class UInputKeySelector;
class UImage;

UCLASS(Abstract, Blueprintable)
class MYCOMMONUI_API UMCSettingListItem : public UCommonButtonBase, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void BindWidgetDelegate();
	void UnbindWidgetDelegate();

	void UpdateNameText();
	void UpdateKey();
	void UpdateKeyIconText(const FKey& InDefaultKey, const FKey& InUserKey);

protected:
	UFUNCTION()
	void OnKeySelectorKeySelected(FInputChord InSelectedKey);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> SettingNameText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> DefaultFocusButton;
	
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UImage> KeyIcon;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UInputKeySelector> KeySelector;

	FName SettingTableRowName;
	
	bool bUpdatingKeySelector = false;
};
