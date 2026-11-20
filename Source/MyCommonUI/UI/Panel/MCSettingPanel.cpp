#include "UI/Panel/MCSettingPanel.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "Subsystem/MCGameDataSubsystem.h"
#include "UI/List/MCSettingListItemData.h"

void UMCSettingPanel::NativeConstruct()
{
	Super::NativeConstruct();

	if (SettingList)
	{
		OnSettingListItemSelectionChangedHandle = SettingList->OnItemSelectionChanged().AddUObject(this, &ThisClass::OnSettingListItemSelectionChanged);
	}
}

void UMCSettingPanel::NativeDestruct()
{
	if (SettingList)
	{
		SettingList->OnItemSelectionChanged().Remove(OnSettingListItemSelectionChangedHandle);
	}

	Super::NativeDestruct();
}

void UMCSettingPanel::NativeOnActivated()
{
	Super::NativeOnActivated();

	UpdateSettingList();
}

UWidget* UMCSettingPanel::NativeGetDesiredFocusTarget() const
{
	if (SettingList)
	{
		return SettingList;
	}

	return Super::NativeGetDesiredFocusTarget();
}

void UMCSettingPanel::UpdateSettingList()
{
	if (SettingList == nullptr || SettingType == EMCSettingType::None)
	{
		return;
	}

	SettingList->ClearListItems();

	if (UGameInstance* GameInstance = GetGameInstance())
	{	
		if (UMCGameDataSubsystem* GameDataSubsystem = GameInstance->GetSubsystem<UMCGameDataSubsystem>())
		{
			if (const UDataTable* SettingDataTable = GameDataSubsystem->GetDataTable<FMCSettingTableRowData>())
			{				
				TArray<TPair<FName, int32>> RowOrderArray;
				
				SettingDataTable->ForeachRow<FMCSettingTableRowData>(TEXT("UMCSettingPanel::NativeOnActivated"),
					[this, &RowOrderArray](const FName& InRowName, const FMCSettingTableRowData& InRowData)
					{
						if (InRowData.Type == SettingType)
						{
							RowOrderArray.Emplace(InRowName, InRowData.DisplayOrder);
						}
					});

				RowOrderArray.Sort([](const TPair<FName, int32>& InLeft, const TPair<FName, int32>& InRight)
					{	
						return InLeft.Value < InRight.Value;
					});

				TArray<UMCSettingListItemData*> ListItemArray;
				ListItemArray.Reserve(RowOrderArray.Num());

				for (const TPair<FName, int32>& RowOrder : RowOrderArray)
				{
					UMCSettingListItemData* ItemData = NewObject<UMCSettingListItemData>(this);
					ItemData->RowHandle.DataTable = SettingDataTable;
					ItemData->RowHandle.RowName = RowOrder.Key;
					ListItemArray.Add(ItemData);
				}

				SettingList->SetListItems(ListItemArray);
				SettingList->SetSelectedIndex(0);
			}
		}
	}
}

void UMCSettingPanel::OnSettingListItemSelectionChanged(UObject* InListItemObject)
{
	if (DescText == nullptr)
	{
		return;
	}

	if (const UMCSettingListItemData* SettingListItemData = Cast<UMCSettingListItemData>(InListItemObject))
	{
		if (const FMCSettingTableRowData* SettingTableRowData = SettingListItemData->RowHandle.GetRow<FMCSettingTableRowData>(TEXT("UMCSettingPanel::OnSettingListItemSelectionChanged")))
		{
			DescText->SetText(SettingTableRowData->Description);
		}
	}
}
