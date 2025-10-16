
# Practica Extraordinaria UI.

## Input

Para abrir el menu de talentos, solo hay que empezar el juego y pulsar la tecla 'T'.

## Memoria

Para esta practica, siguiendo las especificaciones del enunciado, he usado C++ siempre que he podido. Para ello he optado por crear los Widgets a mano, en forma de UTalentWidget y UTalentTreeWidget.

El primero de estos contiene la informacion del boton, el texto que especifica la mejora, el precio y el delegado de "pulsar".

```
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
```

El segundo widget es quien contra todos los TalentWidgets individuales, controlando la posicion y la visiblidad.

```
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
```

Hablando de visibilidad, para controlar si un nodo se puede pulsar o no, habra que tener en cuenta los prerequisitos, el cual hago solo cuando se ha comprado un talento, para no estar comprobandolo cada frame.

```
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
```

Por ultimo, las dos unicas instancias donde tuve que usar blueprints fue para el input, ya que unreal usa su nuevo sistema donde se usan Input Actions y este necesita de blueprint.

La segunda instancia fue para implementar los widgets, que tambien hay que usar su sistema si o si. A esto le he sumado un DataAsset para la escalabilidad facil de talentos nuevos, asi como listar todos los disponibles que ya existen.
