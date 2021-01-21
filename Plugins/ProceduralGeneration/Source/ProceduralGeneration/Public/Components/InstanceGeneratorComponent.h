#pragma once

#include "CoreMinimal.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ParametricMeshComponent.h"
#include "Generators/ParametricGenerator.h"

#include "InstanceGeneratorComponent.generated.h"

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALGENERATION_API UInstanceGeneratorComponent : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface* Material;

	void SetParametricGenerator(TSharedPtr<FParametricGenerator> NewParametricGenerator);

	FVector Start;
	FVector End;

	FRotator SpawnRotation;

	float Offset;
	float Size;

	void Update();
private:
	TSharedPtr<FParametricGenerator> MeshGenerator;

	FDynamicMesh3 DynamicMesh;
};