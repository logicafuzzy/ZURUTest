#include "ParametricMeshComponent.h"


//void RTGUtils::UpdateStaticMeshFromDynamicMesh(
//	UStaticMesh* StaticMesh,
//	const FDynamicMesh3* Mesh)
//{
//	FMeshDescription MeshDescription;
//	FStaticMeshAttributes StaticMeshAttributes(MeshDescription);
//	StaticMeshAttributes.Register();
//
//	FDynamicMeshToMeshDescription Converter;
//	Converter.Convert(Mesh, MeshDescription);
//
//	// todo: vertex color support
//
//	//UStaticMesh* StaticMesh = NewObject<UStaticMesh>(Component);
//	//FName MaterialSlotName = StaticMesh->AddMaterial(MyMaterial);
//
//	// Build the static mesh render data, one FMeshDescription* per LOD.
//	TArray<const FMeshDescription*> MeshDescriptionPtrs;
//	MeshDescriptionPtrs.Emplace(&MeshDescription);
//	StaticMesh->BuildFromMeshDescriptions(MeshDescriptionPtrs);
//}

void UParametricMeshComponent::UpdateMesh() 
{
	check(UpdateStrategy != nullptr && "Update strategy is null in UpdateMesh");
	check(MeshGenerator != nullptr && "Mesh generator is null in UpdateMesh");

	if (UpdateStrategy != nullptr && MeshGenerator != nullptr)
	{
		auto NewParams = UpdateStrategy->DoParametersUpdate(MeshParams);
		MeshGenerator->MeshParams = NewParams;
		MeshGenerator->Generate();
	}
}