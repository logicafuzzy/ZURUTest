#include "ParametersUpdateStrategy.h"


FMeshParams UParametersUpdateStrategy::DoParametersUpdate_Implementation(const FMeshParams& Input)
{
	auto Output = FMeshParams(Input);
	return MoveTemp(Output);
}