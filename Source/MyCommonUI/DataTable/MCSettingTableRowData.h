#pragma once

#include "Engine/DataTable.h"
#include "MCSettingTableRowData.generated.h"

UENUM()
enum class EMCSettingType : uint8
{
	None,
	KeyboardMouse UMETA(DisplayName = "Keyboard and Mouse"),
	Gamepad
};

USTRUCT(BlueprintType)
struct MYCOMMONUI_API FMCSettingTableRowData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "MyCommonUI")
	EMCSettingType Type = EMCSettingType::None;

	UPROPERTY(EditAnywhere, Category = "MyCommonUI")
	FText DisplayName;

	UPROPERTY(EditAnywhere, Category = "MyCommonUI", meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, Category = "MyCommonUI")
	int32 DisplayOrder = 0;

	UPROPERTY(EditAnywhere, Category = "MyCommonUI", meta = (EditCondition = "Type == EMCSettingType::KeyboardMouse || Type == EMCSettingType::Gamepad", EditConditionHides))
	FName InputMappingName;
};
