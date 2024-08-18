// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "S_InteractionInferface.generated.h"

class AS_CharacterPlayer;
// 상호작용
UENUM()
enum class EInteractableType : uint8
{
	Pickup UMETA(DisplayName = "줍기"),
	NonPlayerCharacter UMETA(DisplayName = "NPC"),
	Device UMETA(DisplayName = "장치"),
	Toggle UMETA(DisplayName = "버튼"),
	Container UMETA(DisplayName = "상자")
};

USTRUCT()
struct FInteractableData
{
	GENERATED_BODY();

	FInteractableData() :
		InteractableType(EInteractableType::Pickup),
		Name(FText::GetEmpty()),
		Action(FText::GetEmpty()),
		Quantity(0),
		InteractionDuration(0.0f)
	{

	};

	UPROPERTY(EditInstanceOnly) // 프로퍼티가 인스턴스 편집을 통해서만 수정 가능하도록 설정
	EInteractableType InteractableType;

	UPROPERTY(EditInstanceOnly)
	FText Name;

	// 오브젝트와 상호작용할 때 플레이어에게 표시될 행동(액션)을 정의
	UPROPERTY(EditInstanceOnly)
	FText Action;

	// Pickup 타입의 오브젝트에서 사용될 것
	UPROPERTY(EditInstanceOnly)
	int8 Quantity;

	// 오브젝트와의 상호작용에 필요한 시간(지속 시간)을 정의, 문을 여는 데 걸리는 시간이나 밸브를 돌리는 데 걸리는 시간과 같은 상호작용에 사용
	UPROPERTY(EditInstanceOnly)
	float InteractionDuration;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class US_InteractionInferface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SINGLEPROJECT_API IS_InteractionInferface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteract();
	virtual void EndInteract();
	virtual void Interact(AS_CharacterPlayer* PlayerCharacter);

	FInteractableData InteractableData;
};
