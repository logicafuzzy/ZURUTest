#pragma once

#include "CoreMinimal.h"
#include "Generators/ParametricGenerator.h"

#include "ParametersUpdateStrategy.generated.h"


UCLASS(Abstract)
class PROCEDURALGENERATION_API UParametersUpdateStrategy : public UObject
{
	GENERATED_BODY()
	
public:

	virtual FMeshParams DoParametersUpdate(const FMeshParams& Input) const;
};