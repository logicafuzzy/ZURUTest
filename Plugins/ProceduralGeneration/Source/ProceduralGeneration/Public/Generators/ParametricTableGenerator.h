#pragma once

#include "CoreMinimal.h"

#include "Generators/ParametricGenerator.h"
#include "Generators/TableGenerator.h"

//deprecated
class PROCEDURALGENERATION_API FParametricTableGenerator : public FParametricGenerator
{
public:
	FParametricTableGenerator();

	FName WidthParamName;
	FName LengthParamName;
	FName HeightParamName;

	virtual FMeshShapeGenerator& Generate() override;

protected:
	FTableGenerator* TableGenerator;
};