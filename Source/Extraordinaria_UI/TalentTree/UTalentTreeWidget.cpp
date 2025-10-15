
#include "UTalentTreeWidget.h"

#include "FTalent.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Kismet/KismetMathLibrary.h"
#include "UTalentWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Extraordinaria_UI/Extraordinaria_UICharacter.h"
#include "Kismet/GameplayStatics.h"

void UTalentTreeWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (!RootCanvas) return;
    if (!TalentTreeAsset) return;
    if (!NodeWidgetClass) return;
    if (!PuntosText) return;

    AExtraordinaria_UICharacter* Player =
        Cast<AExtraordinaria_UICharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    
    PuntosText->SetText(FText::AsNumber(Player->TalentPoints));
    
    SpawnNodes();
}

void UTalentTreeWidget::SpawnNodes()
{
    for (const FTalent& Talent : TalentTreeAsset->Talents)
    {
        UTalentWidget* Node = CreateWidget<UTalentWidget>(GetWorld(), NodeWidgetClass);
        
        if (!Node)
            continue;
        
        Node->Create(Talent.Id, Talent.Name, FText::AsNumber(Talent.Cost), Talent.Prerequisites.IsEmpty());
        Node->OnTalentClicked.AddDynamic(this, &UTalentTreeWidget::HandleTalentClicked);
        
        USizeBox* SB = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
        SB->SetWidthOverride(NodeSize.X);
        SB->SetHeightOverride(NodeSize.Y);
        SB->AddChild(Node);

        UCanvasPanelSlot* CPS = RootCanvas->AddChildToCanvas(SB);
        CPS->SetAutoSize(false);
        CPS->SetSize(NodeSize);
        CPS->SetPosition(Talent.UIPosition);

        NodeMap.Add(Talent.Id, Node);
    }
}

FTalent UTalentTreeWidget::GetTalent(const FName TalentID)
{
    for (const FTalent& Talent : TalentTreeAsset->Talents)
        if (Talent.Id == TalentID)
            return Talent;

    return FTalent();
}

UTalentWidget* UTalentTreeWidget::GetTalentWidget(const FName TalentID)
{
    for (auto& Elem : NodeMap)
        if (Elem.Value->TalentID == TalentID)
            return Elem.Value;

    return nullptr;
}

void UTalentTreeWidget::UpdateVisibility()
{
    for (const FTalent& Talent : TalentTreeAsset->Talents)
    {
        TArray<FName> Prerequisites = Talent.Prerequisites;

        for (const FTalent& T : TalentTreeAsset->Talents)
        {
            if (Prerequisites.IsEmpty())
                break;
            
            if (Prerequisites.Contains(T.Id) && Bought.Contains(T.Id))
                Prerequisites.Remove(T.Id);
        }  

        if (Prerequisites.IsEmpty() && !Bought.Contains(Talent.Id))
            GetTalentWidget(Talent.Id)->Button->SetIsEnabled(true);
    }
}

void UTalentTreeWidget::HandleTalentClicked(FName TalentID)
{
    AExtraordinaria_UICharacter* Player =
        Cast<AExtraordinaria_UICharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    FTalent Talent = GetTalent(TalentID);
    
    if (Player->TalentPoints >= Talent.Cost)
    {
        Player->TalentPoints -= Talent.Cost;
        NodeMap[TalentID]->SetIsEnabled(false);
        Bought.Add(Talent.Id);
        PuntosText->SetText(FText::AsNumber(Player->TalentPoints));

        UpdateVisibility();
    }
}

