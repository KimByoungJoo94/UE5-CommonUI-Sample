#pragma once

#include "CommonButtonBase.h"
#include "MCTabButton.generated.h"

class UTextBlock;

UCLASS(Abstract, Blueprintable)
class MYCOMMONUI_API UMCTabButton : public UCommonButtonBase
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LabelText;

	UPROPERTY(EditAnywhere, Category = "MyCommonUI")
	FText ButtonLabel;

	UPROPERTY(EditAnywhere, Category = "MyCommonUI")
	FName TextRowName;
};
