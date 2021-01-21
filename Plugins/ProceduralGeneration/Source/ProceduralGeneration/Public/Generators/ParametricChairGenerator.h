#pragma once

#include "CoreMinimal.h"

#include "Generators/ParametricGenerator.h"
#include "Generators/ChairGenerator.h"

//deprecated
class PROCEDURALGENERATION_API FParametricChairGenerator : public FParametricGenerator
{
public:
	FParametricChairGenerator();

	FName WidthParamName;
	FName LengthParamName;
	FName HeightParamName;
	FName BackHeightParamName;

	virtual FMeshShapeGenerator& Generate() override;

protected:
	FChairGenerator* ChairGenerator;
};