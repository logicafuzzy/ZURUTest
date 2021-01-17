#include "Components/ManipulatorComponent.h"

#include "Components/ParametricMeshComponent.h"

//https://www.youtube.com/watch?v=XVND_jo-kNo&ab_channel=Lusiogenic

UManipulatorComponent::UManipulatorComponent()
	: Super()
	, ParametricMeshComponent(nullptr)
	, OriginParamName(TEXT("Origin"))
	, CornerParamName(TEXT("Corner"))

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