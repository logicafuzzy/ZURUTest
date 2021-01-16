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
	//Input parameter
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Parameters | Input")
	FName CornerParamName = FName(TEXT("Corner"));

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Parameters | Input")
	FName OriginParamName = FName(TEXT("Origin"));

	//Output parameter
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Parameters | Output")
	FName WidthParamName = FName(TEXT("Width"));

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Parameters | Output")
	FName LengthParamName = FName(TEXT("Length"));

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Parameters | Output")
	FName HeightParamName = FName(TEXT("Height"));

	virtual FMeshParams DoParametersUpdate(const UMeshComponent* MeshComponent, const FMeshParams& NewParams) const override;
};