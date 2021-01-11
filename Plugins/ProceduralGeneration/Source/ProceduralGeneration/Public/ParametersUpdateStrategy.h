#pragma once

#include "CoreMinimal.h"
#include "Generators/ParametricGenerator.h"

#include "ParametersUpdateStrategy.generated.h"

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALGENERATION_API UParametersUpdateStrategy : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent)
	FMeshParams DoParametersUpdate(const FMeshParams& Input);
	FMeshParams DoParametersUpdate_Implementation(const FMeshParams& Input);
};