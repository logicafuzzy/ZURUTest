
#include "ResizableActor.h" 

AResizableActor::AResizableActor()
	: Super()
{
	ResizableMeshComponent = CreateDefaultSubobject<UParametricMeshComponent>(TEXT("ParametricMeshComponent"));
	RootComponent = ResizableMeshComponent;
}