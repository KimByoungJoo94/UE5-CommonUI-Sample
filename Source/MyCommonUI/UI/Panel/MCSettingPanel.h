#pragma once

#include "UI/Panel/MCPanelWidget.h"
#include "DataTable/MCSettingTableRowData.h"
#include "MCSettingPanel.generated.h"

class UCommonListView;
class UCommonTextBlock;

UCLASS(Abstract, Blueprintable)
class MYCOMMONUI_API UMCSettingPanel : public UMCPanelWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;	
	virtual void NativeDestruct() override;
	virtual void NativeOnActivated() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

	void UpdateSettingList();
	
	void OnSettingListItemSelectionChanged(UObject* InListItemObject);

private:
	UPROPERTY(EditAnywhere, Category = "MyCommonUI")
	EMCSettingType SettingType = EMCSettingType::None;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonListView> SettingList;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> DescText;

private:
	FDelegateHandle OnSettingListItemSelectionChangedHandle;
};
