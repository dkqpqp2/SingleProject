// Fill out your copyright notice in the Description page of Project Settings.


#include "S_InteractionWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interfaces/S_InteractionInferface.h"


void US_InteractionWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    InteractionProgressBar->PercentDelegate.BindUFunction(this, "UpdeteInteractionProgress");

}

void US_InteractionWidget::NativeConstruct()
{
    Super::NativeConstruct();

    KeyPressText->SetText(FText::FromString(TEXT("클릭")));
    CurrentInteractionDuration = 0.0f;
}

void US_InteractionWidget::UpdateWidget(const FInteractableData* InteractableData) const
{
    switch(InteractableData->InteractableType)
    {
    case EInteractableType::Pickup:
        KeyPressText->SetText(FText::FromString(TEXT("클릭")));
        InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
        if (InteractableData->Quantity < 2)
        {
            QuantityText->SetVisibility(ESlateVisibility::Collapsed);
        }
        else
        {
            QuantityText->SetText(FText::Format(NSLOCTEXT("InteractionWidget", "QuantityText", "x{0}"),
                InteractableData->Quantity));
            QuantityText->SetVisibility(ESlateVisibility::Visible);
        }
        break;
    case EInteractableType::NonPlayerCharacter:
        break;
    case EInteractableType::Device:
        break;
    case EInteractableType::Toggle:
        break;
    case EInteractableType::Container:
        break;
    default:;
    }
    ActionText->SetText(InteractableData->Action);
    NameText->SetText(InteractableData->Name);
}

float US_InteractionWidget::UpdeteInteractionProgress()
{
    return 0.0f;
}