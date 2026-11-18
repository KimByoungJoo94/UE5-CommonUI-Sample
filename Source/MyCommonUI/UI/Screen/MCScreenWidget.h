#pragma once

#include "CommonActivatableWidget.h"
#include "MCScreenWidget.generated.h"

UCLASS(Abstract, Blueprintable)
class MYCOMMONUI_API UMCScreenWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UMCScreenWidget(const FObjectInitializer& InObjectInitializer);

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
};
