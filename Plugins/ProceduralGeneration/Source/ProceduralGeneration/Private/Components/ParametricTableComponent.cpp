#include "Components/ParametricTableComponent.h"

#include "Generators/ParametricTableGenerator.h"
#include "UpdateStrategies/AABBResizeUpdateStrategy.h"


UParametricTableComponent::UParametricTableComponent()
{
	auto Strategy = CreateDefaultSubobject<UAABBResizeUpdateStrategy>(TEXT("AABBResizeUpdateStrategy"));
	auto Generator = MakeShared<FParametricTableGenerator>();

	this->SetParametersUpdateStrategy(Strategy);
	this->MeshGenerator = Generator;

	MeshParams.VectorParams.Add(Strategy->OriginParamName, { 0, 0, 0 });
	MeshParams.VectorParams.Add(Strategy->CornerParamName, { 100, 100, 0 });
	MeshParams.ScalarParams.Add(Generator->WidthParamName, 100);
	MeshParams.ScalarParams.Add(Generator->LengthParamName, 100);
	MeshParams.ScalarParams.Add(Generator->HeightParamName, 85);

	bBuildCollision = true;
}

void UParametricTableComponent::PostUpdateStrategy_Implementation(const FMeshParams& UpdatedParams)
{
	Super::PostUpdateStrategy_Implementation(UpdatedParams);
}