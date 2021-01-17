#include "Components/ManipulatorComponent.h"

#include "Components/ParametricMeshComponent.h"

UManipulatorComponent::UManipulatorComponent()
	: Super()
	, OriginParamName(TEXT("Origin"))
	, CornerParamName(TEXT("Corner"))
	, ParametricMeshComponent(nullptr)

{
	OriginComponent	= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OriginComponent"));
	OriginComponent->SetupAttachment(this);

	CornerComponent	= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CornerComponent"));
	CornerComponent->SetupAttachment(this);

	BottomRightComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomRightComponent"));
	BottomRightComponent->SetupAttachment(this);
	
	TopLeftComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopLeftComponent"));
	TopLeftComponent->SetupAttachment(this);
}

void UManipulatorComponent::SetParametricMesh(UParametricMeshComponent* NewParametricMeshComponent)
{
	this->ParametricMeshComponent = NewParametricMeshComponent;
}