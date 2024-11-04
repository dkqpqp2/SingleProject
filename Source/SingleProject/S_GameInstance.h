// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "S_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEPROJECT_API US_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public: 
	static US_GameInstance* Get(const UObject* InWorldContext);
	template <typename T>
	static const T* GetData(const UObject* InWorldContext, const FName& InID);

	template<typename T>
	const T* GetData(const FName& InID) const;

	template<typename T>
	TArray<FName> GetAllDataID() const;

protected:
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UDataTable>> AllTable;
};

// const T* 사용 하므로 데이터 변경없이 읽기 전용으로 사용할거임
template<typename T>
const T* US_GameInstance::GetData(const UObject* InWorldContext, const FName& InID)
{
	return Get(InWorldContext)->GetData<T>(InID);
}

template<typename T>
const T* US_GameInstance::GetData(const FName& InID) const
{
	for (const auto& DataTable : AllTable)
	{
		// GetRowStruct()는 현재 데이터 테이블의 행 구조를 반환
		// T::StaticStruct()는 템플릿 타입 T의 구조를 반환
		if (DataTable->GetRowStruct() != T::StaticStruct())
		{
			continue;
		}

		// GetRowMap()은 데이터 테이블의 행을 키-값 쌍으로 저장한 맵을 반환
		// Contains(InID)로 ID가 맵에 존재하는지 확인
		if (!DataTable->GetRowMap().Contains(InID))
		{
			continue;
		}

		const uint8* Data = *(DataTable->GetRowMap().Find(InID));
		if (Data == nullptr)
		{
			break;
		}

		// reinterpret_cast는 C++에서 제공하는 타입 캐스팅 연산자 중 하나로, 포인터나 참조를 다른 타입으로 변환하는 데 사용
		return reinterpret_cast<const T*>(Data);
	}
	return nullptr;
}

template<typename T>
TArray<FName> US_GameInstance::GetAllDataID() const
{
	TArray<FName> NameList;

	for (const auto& DataTable : AllTable)
	{
		if (DataTable->GetRowStruct() == T::StaticStruct())
		{
			NameList = DataTable->GetRowNames();
			break;
		}
	}

	return NameList;
}