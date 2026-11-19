#include "UI/Parts/MCTabButton.h"

#include "Components/TextBlock.h"

void UMCTabButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (LabelText == nullptr)
	{
		return;
	}

	if (TextRowName.IsNone())
	{
		if (ButtonLabel.IsEmpty() == false)
		{
			LabelText->SetText(ButtonLabel);
		}
	}
	else
	{
		// 데이터테이블 및 언어 설정으로 확장 예정
	}
}
