#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "CommonButtonBase.h"
#include "MCSettingListItem.generated.h"

UCLASS(Abstract, Blueprintable)
class MYCOMMONUI_API UMCSettingListItem : public UCommonButtonBase, public IUserObjectListEntry
{
	GENERATED_BODY()
};
