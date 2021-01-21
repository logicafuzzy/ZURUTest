#include "Components/InstanceGeneratorComponent.h"

#include "UpdateStrategies/DefaultParametersUpdateStrategy.h"
#include "Generators/MeshGeneratorUtils.h"

#include "DrawDebugHelpers.h"

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
	
	FVector  Dir = End - Start;
	const float L = Dir.Size() - 2 * Offset; //not using all length: leave a margin
	int n = FMath::FloorToInt((L + Offset) / (Size + Offset));
	const FVector center = Start + Dir / 2.0f;
	float off = Offset / 2.0;	

	if (n == 0) 
		return;
	
	Dir.Normalize();

	if(n % 2)
	{
		//odd => mesh starts at the center
		FTransform t(this->SpawnRotation.Quaternion(), center + (Size/2.0)*Dir);
		this->AddInstance(t);

		n--;

		off = Size/2.0 + Offset;
	}
	for (int i = 0; i < n / 2; ++i)
	{
		//spawn two at a time
		const FTransform tR(this->SpawnRotation.Quaternion(), center + (Size + i*(Size + Offset) + off)*Dir);
		this->AddInstance(tR);
		
		const FTransform tL(this->SpawnRotation.Quaternion(), center - (i * (Size + Offset) + off)*Dir);
		this->AddInstance(tL);
	}
}