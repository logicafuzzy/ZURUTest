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

	friend UParametersUpdateStrategy;
public:

	UParametricMeshComponent();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FMeshParams MeshParams;

	UFUNCTION(Blueprintcallable)
	void UpdateMesh(const FMeshParams& NewParams);

	UFUNCTION()
	void SetParametersUpdateStrategy(UParametersUpdateStrategy* NewUpdateStrategy);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface* Material;

	UFUNCTION(BlueprintNativeEvent)
	void PostUpdateStrategy(const FMeshParams& UpdatedParams);

	void SetMeshGenerator(TSharedPtr<FParametricGenerator> MeshGenerator);

protected:
	TSharedPtr<FParametricGenerator> MeshGenerator;

private:

	void UpdateStaticMeshFromDynamicMesh(UStaticMesh* InStaticMesh, const FDynamicMesh3& Mesh);
	
	// Initialized as UDefaultParametersUpdateStrategy 
	UPROPERTY()
	UParametersUpdateStrategy* UpdateStrategy;

	FDynamicMesh3 DynamicMesh;
};