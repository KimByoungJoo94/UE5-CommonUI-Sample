#include "Subsystem/MCGameDataSubsystem.h"
#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "CommonUITypes.h"
#include "MyCommonUI.h"

namespace
{
	const FName DataTableDirectory(TEXT("/Game/MyCommonUI/Data/DataTable/Registered"));
}

void UMCGameDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	IAssetRegistry& AssetRegistry = FAssetRegistryModule::GetRegistry();

#if WITH_EDITOR
	AssetRegistry.ScanPathsSynchronous({ DataTableDirectory.ToString() });
#endif

	FARFilter Filter;
	Filter.PackagePaths.Add(DataTableDirectory);
	Filter.ClassPaths.Add(UDataTable::StaticClass()->GetClassPathName());
	Filter.bRecursivePaths = true;
	Filter.bRecursiveClasses = true;

	TArray<FAssetData> AssetDataArray;
	AssetRegistry.GetAssets(Filter, AssetDataArray);

	for (const FAssetData& AssetData : AssetDataArray)
	{
		UDataTable* DataTable = Cast<UDataTable>(AssetData.GetAsset());
		if (DataTable == nullptr)
		{
			UE_LOG(LogMyCommonUI, Warning, TEXT("Failed to load DataTable: %s"), *AssetData.GetObjectPathString());
			continue;
		}

		const UScriptStruct* RowStruct = DataTable->GetRowStruct();
		if (RowStruct == nullptr)
		{
			UE_LOG(LogMyCommonUI, Warning, TEXT("DataTable has no Row Structure: %s"), *DataTable->GetPathName());
			continue;
		}

		if (TObjectPtr<UDataTable>* RegisteredDataTable = DataTableMap.Find(RowStruct))
		{
			UE_LOG(LogMyCommonUI, Error, TEXT("Duplicate DataTable Row Structure %s in %s. Lookup for this Row Structure is disabled."),
				*RowStruct->GetPathName(), *DataTable->GetPathName());
			
			*RegisteredDataTable = nullptr;			
			continue;
		}

		DataTableMap.Add(RowStruct, DataTable);
	}
}

void UMCGameDataSubsystem::Deinitialize()
{
	DataTableMap.Reset();
	Super::Deinitialize();
}
