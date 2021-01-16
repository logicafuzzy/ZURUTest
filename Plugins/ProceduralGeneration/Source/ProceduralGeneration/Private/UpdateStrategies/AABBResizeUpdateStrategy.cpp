#include "UpdateStrategies/AABBResizeUpdateStrategy.h"

FMeshParams UAABBResizeUpdateStrategy::DoParametersUpdate(const UMeshComponent* MeshComponent, const FMeshParams& NewParams) const
{
	FMeshParams Output(NewParams);
	
	FVector Corner;
	FVector Origin;

	if (GetParam(NewParams, CornerParamName, Corner) && GetParam(NewParams, OriginParamName, Origin))
	{
		FVector Size = Corner - Origin;
		Output.ScalarParams.Add(WidthParamName,  Size.X);
		Output.ScalarParams.Add(LengthParamName, Size.Y);
		Output.ScalarParams.Add(HeightParamName, Size.Z);
	}

	return Output;
}