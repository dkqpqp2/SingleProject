#pragma once


#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "F_TCharacterStat.generated.h"

USTRUCT(BlueprintType)
struct F_TCharacterStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	F_TCharacterStat() : STR(0), DEX(0), CON(0), INT(0) {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	int32 STR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	int32 DEX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	int32 CON;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	int32 INT;

	F_TCharacterStat operator+(const F_TCharacterStat& other) const
	{
		F_TCharacterStat Result;
      
		Result.STR = this->STR + other.STR;
		Result.DEX = this->DEX + other.DEX;
		Result.CON = this->CON + other.CON;
		Result.INT = this->INT + other.INT;

		return Result;
	}
};