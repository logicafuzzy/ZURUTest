#pragma once

#include "CoreMinimal.h"
#include "Math/Vector.h"
#include "Generators/SphereGenerator.h"

#include "Generators/ParametricGenerator.h"

class PROCEDURALGENERATION_API FParametricSphereGenerator : public FParametricGenerator
{
public:
	FParametricSphereGenerator();

	const FName RadiusParamName = FName(TEXT("Radius"));

	virtual FMeshShapeGenerator& Generate() override;
private:

	FSphereGenerator* SphereGenerator;
};