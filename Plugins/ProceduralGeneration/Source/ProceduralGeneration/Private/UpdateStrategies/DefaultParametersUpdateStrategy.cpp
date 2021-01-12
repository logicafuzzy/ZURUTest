#include "UpdateStrategies/DefaultParametersUpdateStrategy.h"


FMeshParams UDefaultParametersUpdateStrategy::DoParametersUpdate(const FMeshParams& Input) const
{
	auto Output = FMeshParams(Input);
	return MoveTemp(Output);
}