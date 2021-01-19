#include "MousePawn.h" 

#include "ProceduralGenerationModule.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"

#include "GameFramework/PlayerController.h"
#include "ResizableTable.h"

AMousePawn::AMousePawn()
	: FloorTag(TEXT("Floor"))
	, ActorClassToSpawn(AResizableTable::StaticClass())
	, HitComponent(nullptr)
	, bGrabbing(false)
	, HitDistance(0.f)
{
	auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController != nullptr)
	{
		PlayerController->bEnableClickEvents = true;
		PlayerController->bShowMouseCursor = true;
		PlayerController->InputComponent->BindAction("MouseLeftClicked", IE_Pressed, this, &AMousePawn::OnClick);
		PlayerController->InputComponent->BindAction("MouseLeftClicked", IE_Released, this, &AMousePawn::OnRelease);
	}
	else
	{
		UE_LOG(ProceduralGenerationLog, Error, TEXT("PlayerController is nullptr"));
	}

	SetActorTickEnabled(false);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AMousePawn::OnClick()
{
	auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	FVector Location, Direction;

	PlayerController->DeprojectMousePositionToWorld(Location, Direction);

	FHitResult Hit;
	const bool bUseComplexCollision = true;
	
	UKismetSystemLibrary::LineTraceSingle(this, Location, Location + 10000.0f*Direction, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility), bUseComplexCollision, TArray<AActor*>(), EDrawDebugTrace::Persistent, Hit, true);

	HitComponent = Hit.GetComponent();
	HitDistance = Hit.Distance;

	if (HitComponent)
	{
		if (HitComponent->ComponentHasTag(FloorTag))
		{
			this->GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, Hit.Location, HitComponent->GetComponentRotation());
		} else if (Cast<UManipulatorComponent>(HitComponent->GetAttachParent()))
		{
			SetActorTickEnabled(true);
			bGrabbing = true;

		}
		UE_LOG(ProceduralGenerationLog, Display, TEXT("Hit %s"), *HitComponent->GetFName().ToString());
	}

	UE_LOG(ProceduralGenerationLog, Display, TEXT("Click"));
}

void AMousePawn::Tick(float deltatime)
{
	if (bGrabbing && HitComponent && Cast<UManipulatorComponent>(HitComponent->GetAttachParent()))
	{
		auto ManipulatorComponent = Cast<UManipulatorComponent>(HitComponent->GetAttachParent());

		auto DrivingComponent = Cast<UStaticMeshComponent>(HitComponent);
		check(DrivingComponent);

		auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		check(PlayerController);

		FVector Location, Direction;
		PlayerController->DeprojectMousePositionToWorld(Location, Direction);

		//Location.Z = DrivingComponent->GetComponentLocation().Z;

		DrivingComponent->SetWorldLocation(Location + HitDistance*Direction);

		//ManipulatorComponent->UpdateParametricMesh(DrivingComponent);
	}
}

void AMousePawn::OnRelease()
{
	bGrabbing = false;
	HitComponent = nullptr;
	HitDistance = 0.f;
}