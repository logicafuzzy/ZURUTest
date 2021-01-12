#pragma once

#include "CoreMinimal.h"

#include "Components/StaticMeshComponent.h"
#include "DynamicMesh3.h"

#include "Generators/ParametricGenerator.h"
#include "UpdateStrategies/ParametersUpdateStrategy.h"

#include "ParametricMeshComponent.generated.h"

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALGENERATION_API UParametricMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UParametricMeshComponent();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FMeshParams MeshParams;

	UFUNCTION(Blueprintcallable)
	void UpdateMesh();

	UFUNCTION()
	void SetParametersUpdateStrategy(UParametersUpdateStrategy* NewUpdateStrategy);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface* Material;

protected:
	TSharedPtr<FParametricGenerator> MeshGenerator;

	void UpdateStaticMeshFromDynamicMesh(UStaticMesh* InStaticMesh, const FDynamicMesh3& Mesh);

private:
	// Initialized as UDefaultParametersUpdateStrategy 
	UPROPERTY()
	UParametersUpdateStrategy* UpdateStrategy;

	FDynamicMesh3 DynamicMesh;
};