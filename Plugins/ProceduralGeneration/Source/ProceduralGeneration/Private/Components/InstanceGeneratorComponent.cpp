#include "Components/InstanceGeneratorComponent.h"

#include "UpdateStrategies/DefaultParametersUpdateStrategy.h"
#include "Generators/MeshGeneratorUtils.h"


void UInstanceGeneratorComponent::SetParametricGenerator(TSharedPtr<FParametricGenerator> NewParametricGenerator)
{
	this->MeshGenerator = NewParametricGenerator;

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
}

void UInstanceGeneratorComponent::Update()
{
	this->ClearInstances();
	//there is always one less spacer than number of elements
	// 1 element 0 spacers
	// |----|..element..|----|
	// 2 elements 1 spacer
	// |----|..element..|spacer|..element..|----|
	// 3 elements 2 spacers
	// |----|..element..|spacer|..element..|----|
	//and so on
	// n*size + (n-1) * offset<= L => n <= (L+offset) / (size+offset)
	const FVector  Dir = End - Start;
	const int n = FMath::FloorToInt((Dir.Size() + Offset) / (Size + Offset));
	const FVector center = Start + 0.5f*(End - Start);

	if (n == 0) return;

	if(n % 2)
	{
		//odd => mesh starts at the center
		FTransform t(this->SpawnRotation.Quaternion(), center - (Size/2.0)*Dir);
		this->AddInstance(t);
	}
	else
	{
		//even => offset at the center

	}

}