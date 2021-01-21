#pragma once

#include "CoreMinimal.h"

#include "Components/StaticMeshComponent.h"
#include "DynamicMesh3.h"

#include "Generators/ParametricGenerator.h"
#include "UpdateStrategies/ParametersUpdateStrategy.h"

#include "ParametricMeshComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateMesh, const FMeshParams&, MeshParams);

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
	virtual void PostUpdateStrategy_Implementation(const FMeshParams& UpdatedParams);

	void SetMeshGenerator(TSharedPtr<FParametricGenerator> MeshGenerator);

	UPROPERTY(BlueprintAssignable, Category = "Test")
	FOnUpdateMesh EventUpdateMesh;

protected:
	TSharedPtr<FParametricGenerator> MeshGenerator;

	virtual void PostSetMeshGenerator() {};

private:
	
	// Initialized as UDefaultParametersUpdateStrategy 
	UPROPERTY()
	UParametersUpdateStrategy* UpdateStrategy;

	FDynamicMesh3 DynamicMesh;
};