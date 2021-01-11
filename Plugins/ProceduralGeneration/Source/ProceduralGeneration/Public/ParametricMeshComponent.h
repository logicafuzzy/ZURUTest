#pragma once

#include "CoreMinimal.h"

#include "Components/MeshComponent.h"
#include "Generators/ParametricGenerator.h"
#include "ParametersUpdateStrategy.h"

#include "ParametricMeshComponent.generated.h"

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALGENERATION_API UParametricMeshComponent : public UMeshComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite)
	UParametersUpdateStrategy* UpdateStrategy;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FMeshParams MeshParams;

	UFUNCTION(Blueprintcallable)
	void UpdateMesh();

protected:
	FParametricGenerator* MeshGenerator;

private:

};