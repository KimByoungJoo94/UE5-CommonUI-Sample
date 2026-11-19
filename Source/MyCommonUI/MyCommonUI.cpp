// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyCommonUI.h"
#include "Modules/ModuleManager.h"

#if WITH_EDITOR
#include "Config/MCGameConfig.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#endif

/* MC 기본 템플릿과 구분 */
class FMCGameModule : public FDefaultGameModuleImpl
{
#if WITH_EDITOR
public:
	virtual void StartupModule() override
	{
		FDefaultGameModuleImpl::StartupModule();

		if (ISettingsModule* SettingsModule = FModuleManager::LoadModulePtr<ISettingsModule>(TEXT("Settings")))
		{
			UMCGameConfig* GameConfig = GetMutableDefault<UMCGameConfig>();
			if (TSharedPtr<ISettingsSection> Section = SettingsModule->RegisterSettings(TEXT("Project"), TEXT("Game"), TEXT("MCGameConfig"),
				NSLOCTEXT("MyCommonUI", "GameConfigName", "MC Game Config"),
				NSLOCTEXT("MyCommonUI", "GameConfigDescription", "CommonUI input actions shared by screens."), GameConfig))
			{
				Section->OnSave().BindUObject(GameConfig, &UMCGameConfig::SaveToProjectConfig);
				Section->OnSaveDefaults().BindUObject(GameConfig, &UMCGameConfig::SaveToProjectConfig);
			}
		}
	}

	virtual void ShutdownModule() override
	{
		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>(TEXT("Settings")))
		{
			SettingsModule->UnregisterSettings(TEXT("Project"), TEXT("Game"), TEXT("MCGameConfig"));
		}

		FDefaultGameModuleImpl::ShutdownModule();
	}
#endif
};

IMPLEMENT_PRIMARY_GAME_MODULE(FMCGameModule, MyCommonUI, "MyCommonUI");
/* ~MC */

DEFINE_LOG_CATEGORY(LogMyCommonUI)
