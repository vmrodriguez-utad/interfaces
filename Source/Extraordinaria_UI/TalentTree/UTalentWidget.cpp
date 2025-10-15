
#include "UTalentWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UTalentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button)
	{
		Button->OnClicked.RemoveAll(this);
		Button->OnClicked.AddDynamic(this, &UTalentWidget::HandleClicked);
	}
}

void UTalentWidget::Create(const FName ID, const FText& Name, const FText& Cost, const bool bEnabled)
{
	TalentID = ID;

	if (IsValid(NameText))
		NameText->SetText(Name);

	if (IsValid(CostText))
		CostText->SetText(Cost);

	if (Button)
	{
		Button->SetIsEnabled(bEnabled);
		
		Button->OnClicked.RemoveAll(this);
		Button->OnClicked.AddDynamic(this, &UTalentWidget::HandleClicked);
	}
}

// NOTE: Cannot be const.
void UTalentWidget::HandleClicked()
{
	OnTalentClicked.Broadcast(TalentID);
}