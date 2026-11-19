#pragma once

#include "CommonActivatableWidget.h"
#include "MCScreenWidget.generated.h"

class UCommonAnimatedSwitcher;
class UCommonButtonBase;
class UCommonButtonGroupBase;
class UHorizontalBox;

UCLASS(Abstract, Blueprintable)
class MYCOMMONUI_API UMCScreenWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UMCScreenWidget(const FObjectInitializer& InObjectInitializer);

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

private:
	void OnTabSelectionChanged(UCommonButtonBase* InSelectedButton, int32 InTabIndex);
	void OnPreviousTabAction();
	void OnNextTabAction();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> TabButtonContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonAnimatedSwitcher> PanelSwitcher;

	UPROPERTY(Transient)
	TObjectPtr<UCommonButtonGroupBase> TabButtonGroup;

	FUIActionBindingHandle PreviousTabActionHandle;
	FUIActionBindingHandle NextTabActionHandle;
};
