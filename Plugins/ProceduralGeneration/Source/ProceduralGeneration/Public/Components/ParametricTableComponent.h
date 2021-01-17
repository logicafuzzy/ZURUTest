#pragma once

#include "CoreMinimal.h"

#include "Components/ParametricMeshComponent.h"
#include "DynamicMesh3.h"

#include "Generators/ParametricGenerator.h"
#include "UpdateStrategies/ParametersUpdateStrategy.h"

#include "ParametricTableComponent.generated.h"

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALGENERATION_API UParametricTableComponent : public UParametricMeshComponent
{
	GENERATED_BODY()

public:

	UParametricTableComponent();



	virtual void PostUpdateStrategy_Implementation(const FMeshParams& UpdatedParams) override;

};