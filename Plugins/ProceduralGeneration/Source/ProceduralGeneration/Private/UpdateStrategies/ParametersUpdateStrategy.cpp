#include "UpdateStrategies/ParametersUpdateStrategy.h"

FMeshParams UParametersUpdateStrategy::DoParametersUpdate(const UMeshComponent* MeshComponent, const FMeshParams& NewParams) const
{
	FMeshParams Output;
	return MoveTemp(Output);
}

bool UParametersUpdateStrategy::GetParam(const FMeshParams& Params, FName Name, float& Value) const
{
	//TODO make type-specific this line only?
	auto Result = Params.ScalarParams.Find(Name);

	if (Result != nullptr)
	{
		Value = *Result;
		return true;
	}
	else
	{
		UE_LOG(ProceduralGenerationLog, Error, TEXT("Param %s not found"), *Name.ToString());
		return false;
	}
}


bool UParametersUpdateStrategy::GetParam(const FMeshParams& Params, FName Name, FVector& Value) const
{
	//TODO make type-specific this line only?
	auto Result = Params.VectorParams.Find(Name);

	if (Result != nullptr)
	{
		Value = *Result;
		return true;
	}
	else
	{
		UE_LOG(ProceduralGenerationLog, Error, TEXT("Param %s not found"), *Name.ToString());
		return false;
	}
}