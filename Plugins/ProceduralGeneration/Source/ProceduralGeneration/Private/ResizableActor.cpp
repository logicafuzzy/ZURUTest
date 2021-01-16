
#include "ResizableActor.h" 

#include "Generators/ParametricTableGenerator.h"

AResizableActor::AResizableActor()
	: Super()
{
	ResizableMeshComponent = CreateDefaultSubobject<UParametricMeshComponent>(TEXT("ParametricMeshComponent"));
	RootComponent = ResizableMeshComponent;
	ResizableMeshComponent->SetMeshGenerator(MakeShared<FParametricTableGenerator>());



}

void AResizableActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ResizableMeshComponent->UpdateMesh(ResizableMeshComponent->MeshParams);
}
