
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UTalentTree.h"
#include "UTalentTreeWidget.generated.h"

class UTextBlock;
class UCanvasPanel;
class UTalentWidget;

UCLASS()
class UTalentTreeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTalentTree* TalentTreeAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UCanvasPanel* RootCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* PuntosText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTalentWidget> NodeWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D NodeSize = FVector2D(160.f, 56.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ConnectorThickness = 4.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, UTalentWidget*> NodeMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FName> Bought;

	UFUNCTION()
	void HandleTalentClicked(FName TalentID);
	
	virtual void NativeConstruct() override;

	void SpawnNodes();
	FTalent GetTalent(FName TalentID);
	UTalentWidget* GetTalentWidget(FName TalentID);
	void UpdateVisibility();
};
