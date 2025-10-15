
#pragma once

#include "UTalentTree.generated.h"

struct FTalent;

UCLASS(BlueprintType)
class UTalentTree : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Talent Tree")
	TArray<FTalent> Talents;

};