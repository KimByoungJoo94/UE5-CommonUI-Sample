#include "UI/Screen/MCScreenWidget.h"

#include "CommonInputModeTypes.h"
#include "Engine/EngineBaseTypes.h"

UMCScreenWidget::UMCScreenWidget(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	bIsBackHandler = true;
}

TOptional<FUIInputConfig> UMCScreenWidget::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
}
