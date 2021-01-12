#include "UpdateStrategies/ParametersUpdateStrategy.h"

FMeshParams UParametersUpdateStrategy::DoParametersUpdate(const FMeshParams& Input) const
{
	FMeshParams Output;
	return MoveTemp(Output);
}