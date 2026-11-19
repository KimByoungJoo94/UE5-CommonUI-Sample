#include "Config/MCGameConfig.h"

#include "Misc/ConfigCacheIni.h"
#include "Misc/Paths.h"

void UMCGameConfig::PostInitProperties()
{
	Super::PostInitProperties();

	if (HasAnyFlags(RF_ClassDefaultObject) && GConfig)
	{
		const FString ConfigPath = GetProjectConfigPath();
		GConfig->LoadFile(ConfigPath);
		LoadConfig(nullptr, *ConfigPath);
	}
}

#if WITH_EDITOR
bool UMCGameConfig::SaveToProjectConfig()
{
	const FString ConfigPath = GetProjectConfigPath();
	SaveConfig(CPF_Config, *ConfigPath);
	return true;
}
#endif

FString UMCGameConfig::GetProjectConfigPath()
{
	return FPaths::Combine(FPaths::ProjectConfigDir(), TEXT("MCDefaultGameConfig.ini"));
}
