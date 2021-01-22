#include "UpdateStrategies/DefaultParametersUpdateStrategy.h"


FMeshParams UDefaultParametersUpdateStrategy::DoParametersUpdate(const UMeshComponent* MeshComponent, const FMeshParams& NewParams) const
{
	return NewParams;
}