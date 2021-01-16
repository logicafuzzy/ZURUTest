#pragma once

#include "CoreMinimal.h"

#include "Generators/ParametricGenerator.h"

//TODO: remove this
#include "Generators/TableGenerator.h"

class PROCEDURALGENERATION_API FParametricTableGenerator : public FParametricGenerator
{
public:
	FParametricTableGenerator();

	virtual FMeshShapeGenerator& Generate() override;
};