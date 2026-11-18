#pragma once

#include "CommonActivatableWidget.h"
#include "MCRootLayout.generated.h"

class UCommonActivatableWidgetStack;

UCLASS(Abstract, Blueprintable)
class MYCOMMONUI_API UMCRootLayout : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

	void OpenSettingsScreen();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> ScreenStack;

private:
	UPROPERTY(EditDefaultsOnly, Category = "MyCommonUI")
	TSubclassOf<UCommonActivatableWidget> SettingsScreenClass;

	UPROPERTY(EditDefaultsOnly, Category = "MyCommonUI")
	TSubclassOf<UCommonActivatableWidget> CharacterScreenClass;
};
