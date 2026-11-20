#pragma once

#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MCGameDataSubsystem.generated.h"

UCLASS()
class MYCOMMONUI_API UMCGameDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	template <typename T>
	const UDataTable* GetDataTable() const
	{
		static_assert(TIsDerivedFrom<T, FTableRowBase>::IsDerived, "T must derive from FTableRowBase.");

		const UScriptStruct* RowStruct = T::StaticStruct();
		const TObjectPtr<UDataTable>* FoundDataTable = DataTableMap.Find(RowStruct);
		if (FoundDataTable == nullptr)
		{
			return nullptr;
		}

		return FoundDataTable->Get();
	}

	template <typename T>
	const T* GetDataRow(FName InRowName) const
	{
		const UDataTable* DataTable = GetDataTable<T>();
		if (DataTable == nullptr)
		{
			return nullptr;
		}

		return DataTable->FindRow<T>(InRowName, TEXT("UMCGameDataSubsystem::GetDataRow"));
	}

private:
	UPROPERTY(Transient)
	TMap<TObjectPtr<const UScriptStruct>, TObjectPtr<UDataTable>> DataTableMap;
};
