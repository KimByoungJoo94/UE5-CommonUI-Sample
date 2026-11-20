#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "CommonButtonBase.h"
#include "MCSettingListItem.generated.h"

class UCommonTextBlock;

UCLASS(Abstract, Blueprintable)
class MYCOMMONUI_API UMCSettingListItem : public UCommonButtonBase, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> SettingNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CurrentKeyText;
};
