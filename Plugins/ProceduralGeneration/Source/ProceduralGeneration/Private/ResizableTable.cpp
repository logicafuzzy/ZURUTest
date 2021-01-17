
#include "ResizableTable.h" 

#include "Generators/ParametricTableGenerator.h"
#include "Components/ParametricTableComponent.h"

AResizableTable::AResizableTable()
{
	ResizableMeshComponent = CreateDefaultSubobject<UParametricTableComponent>(TEXT("ParametricMeshComponent"));
	RootComponent = ResizableMeshComponent;
	//ResizableMeshComponent->SetMeshGenerator(MakeShared<FParametricTableGenerator>());
	
	ManipulatorComponent = CreateDefaultSubobject<UManipulatorComponent>(TEXT("ManipulatorComponent"));

	auto AttachmentTransformRule = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	ManipulatorComponent->AttachToComponent(ResizableMeshComponent, AttachmentTransformRule);

}

void AResizableTable::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ResizableMeshComponent->UpdateMesh(ResizableMeshComponent->MeshParams);
}
