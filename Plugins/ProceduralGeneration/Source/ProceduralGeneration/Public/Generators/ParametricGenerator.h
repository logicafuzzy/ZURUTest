#pragma once

#include "CoreMinimal.h"
#include "Math/Vector.h"

#include "Generators/MeshShapeGenerator.h"

#include "ParametricGenerator.generated.h"

USTRUCT(BLueprintable)
struct FMeshParams
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FName, float> ScalarParams;

	UPROPERTY()
	TMap<FName, FVector> VectorParams;
};

class PROCEDURALGENERATION_API FParametricGenerator : public FMeshShapeGenerator
{
public:
	FMeshParams MeshParams;

	virtual FMeshShapeGenerator& Generate() override
	{
		return *this;
	}
};