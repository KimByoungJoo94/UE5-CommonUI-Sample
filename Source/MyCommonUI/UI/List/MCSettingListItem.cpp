#include "UI/List/MCSettingListItem.h"
#include "CommonTextBlock.h"
#include "DataTable/MCSettingTableRowData.h"
#include "UI/List/MCSettingListItemData.h"

void UMCSettingListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if (const UMCSettingListItemData* ItemData = Cast<UMCSettingListItemData>(ListItemObject))
	{
		const FMCSettingTableRowData* Row = ItemData
			? ItemData->RowHandle.GetRow<FMCSettingTableRowData>(TEXT("UMCSettingListItem::NativeOnListItemObjectSet"))
			: nullptr;

		SettingNameText->SetText(Row ? Row->DisplayName : FText::GetEmpty());
	}
}
