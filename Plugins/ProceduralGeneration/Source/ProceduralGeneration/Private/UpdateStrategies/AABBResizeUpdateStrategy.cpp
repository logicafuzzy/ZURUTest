#include "UpdateStrategies/AABBResizeUpdateStrategy.h"
#include "ProceduralGenerationModule.h"

UAABBResizeUpdateStrategy::UAABBResizeUpdateStrategy()
	: CornerParamName(TEXT("Corner"))
	, OriginParamName(TEXT("Origin"))
	, WidthParamName(TEXT("Width"))
	, LengthParamName(TEXT("Length"))
	, HeightParamName(TEXT("Height"))
{}

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
	}

	UE_LOG(ProceduralGenerationLog, Display, TEXT("UAABBResizeUpdateStrategy::DoParametersUpdate()"));
	return Output;
}