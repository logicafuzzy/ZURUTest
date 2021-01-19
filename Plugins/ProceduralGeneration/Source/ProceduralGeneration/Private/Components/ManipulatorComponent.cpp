#include "Components/ManipulatorComponent.h"

#include "Components/ParametricMeshComponent.h"
#include "ProceduralGenerationModule.h"

UManipulatorComponent::UManipulatorComponent()
	: Super()
	, OriginParamName(TEXT("Origin"))
	, CornerParamName(TEXT("Corner"))
	, ParametricMeshComponent(nullptr)

{
	//FStringAssetReference BasicSpherePath(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	//auto SphereHandle = Cast<UStaticMesh>(BasicSpherePath.TryLoad());

	FMeshParams SphereParams;
	SphereParams.ScalarParams.Add(FName(TEXT("Radius")), 5.0f);

	//TODO make it UParametricSphereComponent
	OriginComponent	= CreateDefaultSubobject<UParametricMeshComponent>(TEXT("OriginComponent"));
	OriginComponent->SetupAttachment(this);
	Cast<UParametricMeshComponent>(OriginComponent)->UpdateMesh(SphereParams);

	CornerComponent	= CreateDefaultSubobject<UParametricMeshComponent>(TEXT("CornerComponent"));
	CornerComponent->SetupAttachment(this);
	Cast<UParametricMeshComponent>(CornerComponent)->UpdateMesh(SphereParams);

	BottomRightComponent = CreateDefaultSubobject<UParametricMeshComponent>(TEXT("BottomRightComponent"));
	BottomRightComponent->SetupAttachment(this);
	Cast<UParametricMeshComponent>(BottomRightComponent)->UpdateMesh(SphereParams);
	
	TopLeftComponent = CreateDefaultSubobject<UParametricMeshComponent>(TEXT("TopLeftComponent"));
	TopLeftComponent->SetupAttachment(this);
	Cast<UParametricMeshComponent>(TopLeftComponent)->UpdateMesh(SphereParams);

}

void UManipulatorComponent::SetParametricMesh(UParametricMeshComponent* NewParametricMeshComponent)
{
	this->ParametricMeshComponent = NewParametricMeshComponent;

	InitManipulators(ParametricMeshComponent->MeshParams);

	UpdateParametricMesh(OriginComponent);
	UpdateParametricMesh(CornerComponent);
}

void UManipulatorComponent::UpdateParametricMesh(UStaticMeshComponent* DrivingComponent)
{
	//ensure localtransform is identity relative to parent
	auto LocalTransform = this->GetRelativeTransform();
	if (!LocalTransform.Equals(FTransform::Identity))
	{
		UE_LOG(ProceduralGenerationLog, Warning, TEXT("ManipulatorComponent local transform not Identity"));
	}
	
	UpdateManipulators(DrivingComponent);

	if (this->ParametricMeshComponent)
	{
		this->ParametricMeshComponent->UpdateMesh(MakeParams());
	}
	else
	{
		UE_LOG(ProceduralGenerationLog, Error, TEXT("ParametricMeshComponent not set"));
	}
}

void UManipulatorComponent::InitManipulators(const FMeshParams& MeshParams)
{
	if (MeshParams.VectorParams.Contains(OriginParamName))
		OriginComponent->SetRelativeLocation(*MeshParams.VectorParams.Find(OriginParamName));
	
	if (MeshParams.VectorParams.Contains(CornerParamName))
		CornerComponent->SetRelativeLocation(*MeshParams.VectorParams.Find(CornerParamName));
}

void UManipulatorComponent::UpdateManipulators(UStaticMeshComponent* DrivingComponent)
{
	//update only adjacent corners. Can be simplyfied to make it more elegant and less else-if?
	if (DrivingComponent == OriginComponent)
	{
		MakeEqual(DrivingComponent, BottomRightComponent, { 1, 0, 1 });
		MakeEqual(DrivingComponent, TopLeftComponent,	  { 0, 1, 1 });
	}
	else if (DrivingComponent == BottomRightComponent)
	{
		MakeEqual(DrivingComponent, OriginComponent, { 1, 0, 0 });
		MakeEqual(DrivingComponent, CornerComponent, { 0, 1, 0 });
	}
	else if (DrivingComponent == CornerComponent)
	{
		MakeEqual(DrivingComponent, TopLeftComponent,     { 1, 0, 1 });
		MakeEqual(DrivingComponent, BottomRightComponent, { 0, 1, 1 });

	}
	else if (DrivingComponent == TopLeftComponent)
	{
		MakeEqual(DrivingComponent, CornerComponent, { 1, 0, 0 });
		MakeEqual(DrivingComponent, OriginComponent, { 0, 1, 0 });
	}
}

void UManipulatorComponent::MakeEqual(USceneComponent* Source, USceneComponent* Dest, FVector Mask) const
{
	Dest->SetRelativeLocation(Source->GetRelativeLocation()*Mask + Dest->GetRelativeLocation()*(FVector::OneVector - Mask));
}

FMeshParams UManipulatorComponent::MakeParams() const
{
	FMeshParams MeshParams;
	MeshParams.VectorParams.Add(OriginParamName, OriginComponent->GetRelativeLocation());
	MeshParams.VectorParams.Add(CornerParamName, CornerComponent->GetRelativeLocation());

	return MeshParams;
}