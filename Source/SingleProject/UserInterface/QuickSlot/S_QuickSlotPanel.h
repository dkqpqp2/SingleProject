
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_QuickSlotPanel.generated.h"

class US_QuickSlot;
class UHorizontalBox;

/**
 * 
 */

UCLASS()
class SINGLEPROJECT_API US_QuickSlotPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdateQuickSlots(const TArray<FName>& LearnedSkills);

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<US_QuickSlot> SlotClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> LeftSkillBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> RightSkillBox;

	void AddQuickSlotsToBox(UHorizontalBox* SkillBox, const TArray<FName>& LearnedSkills);
};
