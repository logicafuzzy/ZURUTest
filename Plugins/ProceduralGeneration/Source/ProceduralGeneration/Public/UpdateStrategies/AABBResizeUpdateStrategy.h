#pragma once

#include "CoreMinimal.h"
#include "Generators/ParametricGenerator.h"
#include "UpdateStrategies/ParametersUpdateStrategy.h"

#include "AABBResizeUpdateStrategy.generated.h"

UCLASS(Blueprintable)
class PROCEDURALGENERATION_API UAABBResizeUpdateStrategy : public UParametersUpdateStrategy
{
	GENERATED_BODY()
	
public:

	UAABBResizeUpdateStrategy();

	//Input parameter
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Parameters | Input")
	FName CornerParamName; 

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Parameters | Input")
	FName OriginParamName;

	//Output parameter
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Parameters | Output")
	FName WidthParamName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Parameters | Output")
	FName LengthParamName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Parameters | Output")
	FName HeightParamName; 

	virtual FMeshParams DoParametersUpdate(const UMeshComponent* MeshComponent, const FMeshParams& NewParams) const override;
};