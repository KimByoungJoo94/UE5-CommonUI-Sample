#pragma once

#include "Engine/DataTable.h"
#include "Engine/DeveloperSettings.h"
#include "MCGameConfig.generated.h"

UCLASS(Config = MCDefaultGameConfig, DefaultConfig)
class MYCOMMONUI_API UMCGameConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	const FDataTableRowHandle& GetPreviousTabAction() const { return PreviousTabAction; }
	const FDataTableRowHandle& GetNextTabAction() const { return NextTabAction; }

#if WITH_EDITOR
	virtual bool SupportsAutoRegistration() const override { return false; }
	bool SaveToProjectConfig();
#endif

protected:
	virtual void PostInitProperties() override;

private:
	static FString GetProjectConfigPath();

private:
	UPROPERTY(Config, EditAnywhere, Category = "MyCommonUI", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle PreviousTabAction;

	UPROPERTY(Config, EditAnywhere, Category = "MyCommonUI", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle NextTabAction;
};
