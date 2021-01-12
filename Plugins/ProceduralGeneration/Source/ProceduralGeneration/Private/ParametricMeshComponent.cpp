#include "ParametricMeshComponent.h"

#include "Generators/ParametricSphereGenerator.h"
#include "UpdateStrategies/DefaultParametersUpdateStrategy.h"

#include "MeshDescription.h"
#include "StaticMeshAttributes.h"
#include "DynamicMeshToMeshDescription.h"

UParametricMeshComponent::UParametricMeshComponent()
	: Super()
{
	this->UpdateStrategy = CreateDefaultSubobject<UDefaultParametersUpdateStrategy>(TEXT("DefaultParametersUpdateStrategy"));

	this->MeshGenerator = MakeShared<FParametricSphereGenerator>();

}

void UParametricMeshComponent::UpdateMesh() 
{
	check(this->UpdateStrategy != nullptr && "Update strategy is null in UpdateMesh");
	check(this->MeshGenerator != nullptr && "Mesh generator is null in UpdateMesh");

	auto NewParams = this->UpdateStrategy->DoParametersUpdate(MeshParams);
	this->MeshGenerator->MeshParams = NewParams;
	DynamicMesh.Copy(&MeshGenerator->Generate());

	if (this->GetStaticMesh() == nullptr)
	{
		auto NewStaticMesh = NewObject<UStaticMesh>();
		this->SetStaticMesh(NewStaticMesh);
		NewStaticMesh->StaticMaterials.Add(FStaticMaterial());
	}

	this->UpdateStaticMeshFromDynamicMesh(GetStaticMesh(), DynamicMesh);

	//TODO: support multiple material slots
	UMaterialInterface* UseMaterial = (this->Material != nullptr) ? this->Material : UMaterial::GetDefaultMaterial(MD_Surface);
	this->SetMaterial(0, UseMaterial);
}

void UParametricMeshComponent::SetParametersUpdateStrategy(UParametersUpdateStrategy* NewUpdateStrategy)
{
	check(NewUpdateStrategy != nullptr && "NewUpdateStrategy is not a valid object");

	if (NewUpdateStrategy != nullptr)
		this->UpdateStrategy = NewUpdateStrategy;
}

void UParametricMeshComponent::UpdateStaticMeshFromDynamicMesh(
	UStaticMesh* InStaticMesh,
	const FDynamicMesh3& InMesh)
{
	FMeshDescription MeshDescription;
	FStaticMeshAttributes StaticMeshAttributes(MeshDescription);
	StaticMeshAttributes.Register();

	FDynamicMeshToMeshDescription Converter;
	Converter.Convert(&InMesh, MeshDescription);

	// todo: vertex color support

	//UStaticMesh* StaticMesh = NewObject<UStaticMesh>(Component);
	//FName MaterialSlotName = StaticMesh->AddMaterial(MyMaterial);

	// Build the static mesh render data, one FMeshDescription* per LOD.
	TArray<const FMeshDescription*> MeshDescriptionPtrs;
	MeshDescriptionPtrs.Emplace(&MeshDescription);
	InStaticMesh->BuildFromMeshDescriptions(MeshDescriptionPtrs);
}