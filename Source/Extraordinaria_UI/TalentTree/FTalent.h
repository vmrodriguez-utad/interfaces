
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FTalent.generated.h"

USTRUCT(BlueprintType)
struct FTalent
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName Id;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Cost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D UIPosition = FVector2D::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FName> Prerequisites;
};