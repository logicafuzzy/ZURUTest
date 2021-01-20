#pragma once

#include "CoreMinimal.h"

#include "Generators/MeshShapeGenerator.h"


class PROCEDURALGENERATION_API FTableGenerator : public FMeshShapeGenerator
{
public:
	float width;
	float length;
	float height;
	float topThickness;
	float legThickness;

	FTableGenerator();

	virtual FMeshShapeGenerator& Generate() override;
};


