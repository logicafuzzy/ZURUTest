#pragma once

#include "CoreMinimal.h"

#include "Generators/MeshShapeGenerator.h"


class PROCEDURALGENERATION_API FChairGenerator : public FMeshShapeGenerator
{
public:
	float width;
	float length;
	float height;
	float topThickness;
	float legThickness;
	float backHeight;

	FChairGenerator();

	virtual FMeshShapeGenerator& Generate() override;
};


