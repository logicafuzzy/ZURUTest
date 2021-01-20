#include "Components/ParametricTableComponent.h"

#include "Generators/ParametricTableGenerator.h"
#include "UpdateStrategies/AABBResizeUpdateStrategy.h"


UParametricTableComponent::UParametricTableComponent()
{
	auto Strategy = CreateDefaultSubobject<UAABBResizeUpdateStrategy>(TEXT("AABBResizeUpdateStrategy"));
	auto Generator = MakeShared<FParametricTableGenerator>();

	this->SetParametersUpdateStrategy(Strategy);
	this->MeshGenerator = Generator;
	
	FStringAssetReference TableMaterialPath(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak'"));

	auto TableMaterial = Cast<UMaterialInterface>(TableMaterialPath.TryLoad());
	this->Material = TableMaterial;

	MeshParams.VectorParams.Add(Strategy->OriginParamName, { 0, 0, 100 });
	MeshParams.VectorParams.Add(Strategy->CornerParamName, { 100, 100, 100 });
	MeshParams.ScalarParams.Add(Generator->WidthParamName, 100);
	MeshParams.ScalarParams.Add(Generator->LengthParamName, 100);
	MeshParams.ScalarParams.Add(Generator->HeightParamName, 85);

}

void UParametricTableComponent::PostUpdateStrategy_Implementation(const FMeshParams& UpdatedParams)
{
	Super::PostUpdateStrategy_Implementation(UpdatedParams);
}