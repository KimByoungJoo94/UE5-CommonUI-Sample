#include "UI/MCRootLayout.h"

#include "CommonInputModeTypes.h"
#include "Engine/EngineBaseTypes.h"
#include "Input/UIActionBindingHandle.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

TOptional<FUIInputConfig> UMCRootLayout::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently);
}

void UMCRootLayout::OpenSettingsScreen()
{
	if (ScreenStack && SettingsScreenClass && ScreenStack->GetActiveWidget() == nullptr)
	{
		ScreenStack->AddWidget(SettingsScreenClass);
	}
}
