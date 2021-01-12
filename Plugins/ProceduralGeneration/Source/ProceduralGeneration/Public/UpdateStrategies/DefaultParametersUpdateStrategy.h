#pragma once

#include "CoreMinimal.h"
#include "Generators/ParametricGenerator.h"
#include "UpdateStrategies/ParametersUpdateStrategy.h"

#include "DefaultParametersUpdateStrategy.generated.h"

UCLASS(Blueprintable)
class PROCEDURALGENERATION_API UDefaultParametersUpdateStrategy : public UParametersUpdateStrategy
{
	GENERATED_BODY()
	
public:

	//Inpute parameters are copied and returned as output without further elaborations
	virtual FMeshParams DoParametersUpdate(const FMeshParams& Input) const override;
};