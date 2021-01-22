#pragma once

#include "CoreMinimal.h"
#include "ProceduralGenerationModule.h"

#include "Generators/ParametricGenerator.h"
#include "Components/MeshComponent.h"

#include "ParametersUpdateStrategy.generated.h"


UCLASS(Abstract)
class PROCEDURALGENERATION_API UParametersUpdateStrategy : public UObject
{
	GENERATED_BODY()
	
public:

	virtual FMeshParams DoParametersUpdate(const UMeshComponent* MeshComponent, const FMeshParams& NewParams) const;

protected:
	//TODO push method down to FMeshParams?
	bool GetParam(const FMeshParams& Params, FName Name, float& Value) const;
	bool GetParam(const FMeshParams& Params, FName Name, FVector& Value) const;
};