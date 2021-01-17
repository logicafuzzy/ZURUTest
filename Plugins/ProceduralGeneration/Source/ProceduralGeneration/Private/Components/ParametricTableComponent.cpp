#include "Components/ParametricTableComponent.h"

#include "Generators/ParametricSphereGenerator.h"
#include "UpdateStrategies/AABBResizeUpdateStrategy.h"


UParametricTableComponent::UParametricTableComponent()
{
	this->SetParametersUpdateStrategy(CreateDefaultSubobject<UAABBResizeUpdateStrategy>(TEXT("AABBResizeUpdateStrategy")));
	this->MeshGenerator = MakeShared<FParametricSphereGenerator>();
	
	FStringAssetReference TableMaterialPath(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak'"));

	auto TableMaterial = Cast<UMaterialInterface>(TableMaterialPath.TryLoad());
	this->Material = TableMaterial;
}

void UParametricTableComponent::PostUpdateStrategy_Implementation(const FMeshParams& UpdatedParams)
{
	Super::PostUpdateStrategy_Implementation(UpdatedParams);
}