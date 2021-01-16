#pragma once

#include "CoreMinimal.h"

#include "Generators/MeshShapeGenerator.h"

//TODO: remove this
#include "Generators/SphereGenerator.h"

class PROCEDURALGENERATION_API FTableGenerator : public FMeshShapeGenerator
{
public:
	FTableGenerator();

	FMeshShapeGenerator* temp;

	virtual FMeshShapeGenerator& Generate() override;
};