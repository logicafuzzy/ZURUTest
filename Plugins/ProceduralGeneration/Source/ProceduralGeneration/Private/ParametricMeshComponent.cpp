#include "ParametricMeshComponent.h"

#include "Generators/SphereGenerator.h"
#include "UpdateStrategies/DefaultParametersUpdateStrategy.h"

#include "MeshDescription.h"
#include "StaticMeshAttributes.h"
#include "DynamicMeshToMeshDescription.h"

UParametricMeshComponent::UParametricMeshComponent()
	: Super()
{
	this->UpdateStrategy = NewObject<UDefaultParametersUpdateStrategy>();

	this->MeshGenerator = MakeShared<FParametricGenerator>(new FSphereGenerator());
}

void UParametricMeshComponent::UpdateMesh() 
{
	check(UpdateStrategy != nullptr && "Update strategy is null in UpdateMesh");
	check(MeshGenerator != nullptr && "Mesh generator is null in UpdateMesh");

	auto NewParams = UpdateStrategy->DoParametersUpdate(MeshParams);
	MeshGenerator->MeshParams = NewParams;
	DynamicMesh.Copy(&MeshGenerator->Generate());

	if (GetStaticMesh() == nullptr)
	{
		auto NewStaticMesh = NewObject<UStaticMesh>();
		SetStaticMesh(NewStaticMesh);
		NewStaticMesh->StaticMaterials.Add(FStaticMaterial());
	}

	UpdateStaticMeshFromDynamicMesh(GetStaticMesh(), DynamicMesh);

	//TODO: support multiple material slots
	UMaterialInterface* UseMaterial = (this->Material != nullptr) ? this->Material : UMaterial::GetDefaultMaterial(MD_Surface);
	SetMaterial(0, UseMaterial);
}

void UParametricMeshComponent::SetParametersUpdateStrategy(UParametersUpdateStrategy* NewUpdateStrategy)
{
	check(NewUpdateStrategy == nullptr && "NewUpdateStrategy is not a valid object");

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