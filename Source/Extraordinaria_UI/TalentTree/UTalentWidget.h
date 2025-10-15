
#pragma once

#include "Blueprint/UserWidget.h"
#include "UTalentWidget.generated.h"

class UButton;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTalentClicked, FName, TalentId);

UCLASS(BlueprintType)
class UTalentWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TalentID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* CostText;
	
	UPROPERTY(BlueprintAssignable)
	FOnTalentClicked OnTalentClicked;

	virtual void NativeConstruct() override;
	
	void Create(const FName ID, const FText& Name, const FText& Cost, const bool bEnabled);

	UFUNCTION()
	void HandleClicked();
};
