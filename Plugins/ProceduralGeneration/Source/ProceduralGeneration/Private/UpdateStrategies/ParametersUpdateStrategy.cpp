#include "UpdateStrategies/ParametersUpdateStrategy.h"

FMeshParams UParametersUpdateStrategy::DoParametersUpdate(const UMeshComponent* MeshComponent, const FMeshParams& NewParams) const
{
	FMeshParams Output;
	return MoveTemp(Output);
}

bool UParametersUpdateStrategy::GetParam(const FMeshParams& Params, FName Name, float& Value) const
{
	if (Params.ScalarParams.Contains(Name))
	{
		Value = *Params.ScalarParams.Find(Name);
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
	if (Params.VectorParams.Contains(Name))
	{
		Value = *Params.VectorParams.Find(Name);
		return true;
	}
	else
	{
		UE_LOG(ProceduralGenerationLog, Error, TEXT("Param %s not found"), *Name.ToString());
		return false;
	}
}