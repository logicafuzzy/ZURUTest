#pragma once

#include "CoreMinimal.h"
#include "Math/Vector.h"

#include "Generators/MeshShapeGenerator.h"

#include "ParametricGenerator.generated.h"

USTRUCT(BLueprintable)
struct FMeshParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TMap<FName, float> ScalarParams;

	UPROPERTY(EditAnywhere)
	TMap<FName, FVector> VectorParams;
};

class PROCEDURALGENERATION_API FParametricGenerator : public FMeshShapeGenerator
{
public:
	FMeshParams MeshParams;

	// decorates a MeshShapeGenerator and takes ownership
	FParametricGenerator(FMeshShapeGenerator* MeshShapeGenerator);

	~FParametricGenerator();

	virtual FMeshShapeGenerator& Generate() override;

protected:
	FMeshShapeGenerator* DecoratedMeshShapeGenerator;
};