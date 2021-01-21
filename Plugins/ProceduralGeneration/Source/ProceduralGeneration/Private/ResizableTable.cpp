
#include "ResizableTable.h" 

#include "Generators/ParametricTableGenerator.h"
#include "Components/ParametricTableComponent.h"
#include "Generators/ParametricChairGenerator.h"

AResizableTable::AResizableTable()
{
	FStringAssetReference TableMaterialPath(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak'"));

	auto TableMaterial = Cast<UMaterialInterface>(TableMaterialPath.TryLoad());

	ResizableMeshComponent = CreateDefaultSubobject<UParametricTableComponent>(TEXT("ParametricMeshComponent"));
	ResizableMeshComponent->Material = TableMaterial;
	
	RootComponent = ResizableMeshComponent;

	ManipulatorComponent = CreateDefaultSubobject<UManipulatorComponent>(TEXT("ManipulatorComponent"));

	auto AttachmentTransformRule = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	ManipulatorComponent->AttachToComponent(ResizableMeshComponent, AttachmentTransformRule);
	ManipulatorComponent->SetParametricMesh(ResizableMeshComponent);

	auto ChairGenerator = MakeShared<FParametricChairGenerator>();

	const float Offset = 10.0f;
	const float Size = 45.0f;

	//can be overridden via blueprint
	ChairMeshParams.ScalarParams.Add(ChairGenerator->HeightParamName, Size);
	ChairMeshParams.ScalarParams.Add(ChairGenerator->WidthParamName,  Size);
	ChairMeshParams.ScalarParams.Add(ChairGenerator->LengthParamName, Size);
	ChairMeshParams.ScalarParams.Add(ChairGenerator->BackHeightParamName, Size);

	ChairGenerator->MeshParams = ChairMeshParams;

	//todo: make them share the same instance
	//todo2: too much of a copy paste thing. Make a parametric function instead
	ChairFrontRow = CreateDefaultSubobject<UInstanceGeneratorComponent>(TEXT("ChairFrontRow"));
	ChairFrontRow->Material = TableMaterial;
	ChairFrontRow->SetParametricGenerator(ChairGenerator);
	ChairFrontRow->AttachToComponent(ManipulatorComponent->OriginComponent, AttachmentTransformRule);
	ChairFrontRow->Offset = Offset;
	ChairFrontRow->Size = Size;
	ChairFrontRow->SetRelativeLocation({-Offset, 0, -ManipulatorComponent->GetRelativeLocation().Z });
	ChairFrontRow->SpawnRotation = FRotator::MakeFromEuler({0, 0, -90});

	ChairBackRow = CreateDefaultSubobject<UInstanceGeneratorComponent>(TEXT("ChairBackRow"));
	ChairBackRow->Material = TableMaterial;
	ChairBackRow->SetParametricGenerator(ChairGenerator);
	ChairBackRow->AttachToComponent(ManipulatorComponent->CornerComponent, AttachmentTransformRule);
	ChairBackRow->SetRelativeLocation({ Offset, 0, -ManipulatorComponent->GetRelativeLocation().Z });
	ChairBackRow->Offset = Offset;
	ChairBackRow->Size = Size;
	ChairBackRow->SpawnRotation = FRotator::MakeFromEuler({ 0, 0, 90 });

	ChairLeftRow = CreateDefaultSubobject<UInstanceGeneratorComponent>(TEXT("ChairLeftRow"));
	ChairLeftRow->Material = TableMaterial;
	ChairLeftRow->SetParametricGenerator(ChairGenerator);
	ChairLeftRow->AttachToComponent(ManipulatorComponent->TopLeftComponent, AttachmentTransformRule);
	ChairLeftRow->SetRelativeLocation({ 0, -Offset, -ManipulatorComponent->GetRelativeLocation().Z });
	ChairLeftRow->Offset = Offset;
	ChairLeftRow->Size = Size;
	ChairLeftRow->SpawnRotation = FRotator::MakeFromEuler({ 0, 0, 0 });

	ChairRightRow = CreateDefaultSubobject<UInstanceGeneratorComponent>(TEXT("ChairRightRow"));
	ChairRightRow->Material = TableMaterial;
	ChairRightRow->SetParametricGenerator(ChairGenerator);
	ChairRightRow->AttachToComponent(ManipulatorComponent->BottomRightComponent, AttachmentTransformRule);
	ChairRightRow->SetRelativeLocation({ 0, Offset, -ManipulatorComponent->GetRelativeLocation().Z });
	ChairRightRow->Offset = Offset;
	ChairRightRow->Size = Size;
	ChairRightRow->SpawnRotation = FRotator::MakeFromEuler({ 0, 0, 180 });

	//linking event after initialization of components to avoid use of invalid objects
	ResizableMeshComponent->EventUpdateMesh.AddDynamic(this, &AResizableTable::OnUpdateMesh);
}

void AResizableTable::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ResizableMeshComponent->UpdateMesh(ResizableMeshComponent->MeshParams);
}

void AResizableTable::OnUpdateMesh(const FMeshParams&)
{
	//boring wire-connecting code
	ChairFrontRow->Start = FVector(0, 0, 0);
	ChairFrontRow->End = ManipulatorComponent->BottomRightComponent->GetRelativeLocation() - ManipulatorComponent->OriginComponent->GetRelativeLocation();
	ChairFrontRow->Update();

	ChairBackRow->Start = FVector(0, 0, 0);
	ChairBackRow->End = ManipulatorComponent->TopLeftComponent->GetRelativeLocation() - ManipulatorComponent->CornerComponent->GetRelativeLocation();
	ChairBackRow->Update();

	ChairLeftRow->Start = FVector(0, 0, 0);
	ChairLeftRow->End = ManipulatorComponent->OriginComponent->GetRelativeLocation() - ManipulatorComponent->TopLeftComponent->GetRelativeLocation();
	ChairLeftRow->Update();

	ChairRightRow->Start = FVector(0, 0, 0);
	ChairRightRow->End = ManipulatorComponent->CornerComponent->GetRelativeLocation() - ManipulatorComponent->BottomRightComponent->GetRelativeLocation();
	ChairRightRow->Update();

}
