#include "Components/ParametricTableComponent.h"

#include "Generators/ParametricSphereGenerator.h"
#include "UpdateStrategies/AABBResizeUpdateStrategy.h"


UParametricTableComponent::UParametricTableComponent()
{
	auto Strategy = CreateDefaultSubobject<UAABBResizeUpdateStrategy>(TEXT("AABBResizeUpdateStrategy"));
	auto Generator = MakeShared<FParametricSphereGenerator>();

	this->SetParametersUpdateStrategy(Strategy);
	this->MeshGenerator = Generator;
	
	FStringAssetReference TableMaterialPath(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak'"));

	auto TableMaterial = Cast<UMaterialInterface>(TableMaterialPath.TryLoad());
	this->Material = TableMaterial;

	MeshParams.VectorParams.Add(Strategy->OriginParamName, FVector::ZeroVector);
	MeshParams.VectorParams.Add(Strategy->CornerParamName, FVector::OneVector*100.0f);
	MeshParams.ScalarParams.Add(Generator->RadiusParamName, 10.0f);
}

void UParametricTableComponent::PostUpdateStrategy_Implementation(const FMeshParams& UpdatedParams)
{
	Super::PostUpdateStrategy_Implementation(UpdatedParams);
}