#pragma once

#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "MCSettingListItemData.generated.h"

UCLASS()
class MYCOMMONUI_API UMCSettingListItemData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient)
	FDataTableRowHandle RowHandle;
};
