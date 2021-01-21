#include "Components/ParametricMeshComponent.h"

#include "Generators/ParametricSphereGenerator.h"
#include "UpdateStrategies/DefaultParametersUpdateStrategy.h"

#include "Generators/MeshGeneratorUtils.h"

UParametricMeshComponent::UParametricMeshComponent()
{
	this->UpdateStrategy = CreateDefaultSubobject<UDefaultParametersUpdateStrategy>(TEXT("DefaultParametersUpdateStrategy"));
	this->MeshGenerator = MakeShared<FParametricSphereGenerator>();
}

void UParametricMeshComponent::UpdateMesh(const FMeshParams& NewParams) 
{
	check(this->UpdateStrategy != nullptr && "Update strategy is null in UpdateMesh");
	check(this->MeshGenerator.IsValid() && "Mesh generator is null in UpdateMesh");

	this->PostUpdateStrategy(this->UpdateStrategy->DoParametersUpdate(this, NewParams));

	if (this->GetStaticMesh() == nullptr)
	{
		auto NewStaticMesh = NewObject<UStaticMesh>();
		this->SetStaticMesh(NewStaticMesh);
		NewStaticMesh->StaticMaterials.Add(FStaticMaterial());
	}

	MeshGeneratorUtils::UpdateStaticMesh(MeshGenerator.Get(), GetStaticMesh(), DynamicMesh);

	//TODO: support multiple material slots
	UMaterialInterface* UseMaterial = (this->Material != nullptr) ? this->Material : UMaterial::GetDefaultMaterial(MD_Surface);
	this->SetMaterial(0, UseMaterial);

	EventUpdateMesh.Broadcast(MeshParams);
}

void UParametricMeshComponent::PostUpdateStrategy_Implementation(const FMeshParams& UpdatedParams)
{
	this->MeshGenerator->MeshParams = UpdatedParams;
	this->MeshParams = UpdatedParams;
}

void UParametricMeshComponent::SetParametersUpdateStrategy(UParametersUpdateStrategy* NewUpdateStrategy)
{
	check(NewUpdateStrategy != nullptr && "NewUpdateStrategy is not a valid object");

	if (NewUpdateStrategy != nullptr)
		this->UpdateStrategy = NewUpdateStrategy;
}

void UParametricMeshComponent::SetMeshGenerator(TSharedPtr<FParametricGenerator> NewMeshGenerator)
{
	this->MeshGenerator = NewMeshGenerator;

	this->PostSetMeshGenerator();
}