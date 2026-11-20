#pragma once

#include "Engine/DataTable.h"
#include "Engine/DeveloperSettings.h"
#include "MCGameConfig.generated.h"

UCLASS(Config = MCGameConfig, DefaultConfig, meta = (DisplayName = "MC Game Config"))
class MYCOMMONUI_API UMCGameConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	virtual FName GetCategoryName() const override { return NAME_Game; }

public:
	UPROPERTY(Config, EditAnywhere, Category = "MyCommonUI", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle PreviousTabAction;

	UPROPERTY(Config, EditAnywhere, Category = "MyCommonUI", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle NextTabAction;
};
