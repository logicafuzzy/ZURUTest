#include "MousePawn.h" 

#include "ProceduralGenerationModule.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"

#include "GameFramework/PlayerController.h"
#include "ResizableTable.h"

AMousePawn::AMousePawn()
	: FloorTag(TEXT("Floor"))
	, TableTag(TEXT("Table"))
	, ActorClassToSpawn(AResizableTable::StaticClass())
	, HitComponent(nullptr)
	, bGrabbing(false)
	, HitDistance(0.f)
	, bCameraDragging(false)
{
	SetActorTickEnabled(false);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = false;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController != nullptr)
	{
		PlayerController->bEnableClickEvents = true;
		PlayerController->bShowMouseCursor = true;
		PlayerController->InputComponent->BindAction("MouseLeft", IE_Pressed, this, &AMousePawn::OnClick);
		PlayerController->InputComponent->BindAction("MouseLeft", IE_Released, this, &AMousePawn::OnRelease);
		PlayerController->InputComponent->BindAction("MouseRight", IE_Pressed, this, &AMousePawn::StartDrag);
		PlayerController->InputComponent->BindAction("MouseRight", IE_Released, this, &AMousePawn::StopDrag);
		PlayerController->InputComponent->BindAxis("Yaw", this, &AMousePawn::Yaw);
		PlayerController->InputComponent->BindAxis("Pitch", this, &AMousePawn::Pitch);
	}
	else
	{
		UE_LOG(ProceduralGenerationLog, Error, TEXT("PlayerController is nullptr"));
	}

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(this->RootComponent);
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bEnableCameraRotationLag = true;
	RootComponent = SpringArmComponent;

	SpringArmComponent->CameraLagSpeed = 5.0f;
	SpringArmComponent->CameraRotationLagSpeed = 5.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
}

void AMousePawn::OnClick()
{
	auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	FVector Location, Direction;

	PlayerController->DeprojectMousePositionToWorld(Location, Direction);

	FHitResult Hit;
	const bool bUseComplexCollision = true;
	
	UKismetSystemLibrary::LineTraceSingle(this, Location, Location + 10000.0f*Direction, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility), bUseComplexCollision, TArray<AActor*>(), EDrawDebugTrace::None, Hit, false);

	HitComponent = Hit.GetComponent();
	HitDistance = Hit.Distance;
	HitLocation = Hit.Location;

	if (HitComponent)
	{
		if (HitComponent->ComponentHasTag(FloorTag))
		{
			this->GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, Hit.Location, HitComponent->GetComponentRotation());
		} else if (Cast<UManipulatorComponent>(HitComponent->GetAttachParent()))
		{
			SetActorTickEnabled(true);
			bGrabbing = true;

			DragDelta = Hit.Location - HitComponent->GetComponentLocation();
		}
		else if (HitComponent->ComponentHasTag(TableTag))
		{
			SetActorTickEnabled(true);
			bDragging = true;

			DragDelta = Hit.Location - HitComponent->GetAttachmentRootActor()->GetActorLocation();
		}
		UE_LOG(ProceduralGenerationLog, Display, TEXT("Hit %s"), *HitComponent->GetFName().ToString());
	}
}

void AMousePawn::Tick(float deltatime)
{
	auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	check(PlayerController);

	FVector Location, Direction;
	PlayerController->DeprojectMousePositionToWorld(Location, Direction);

	if (HitComponent)
	{
		if (bGrabbing && Cast<UManipulatorComponent>(HitComponent->GetAttachParent()))
		{
			auto ManipulatorComponent = Cast<UManipulatorComponent>(HitComponent->GetAttachParent());

			auto DrivingComponent = Cast<UStaticMeshComponent>(HitComponent);
			check(DrivingComponent);

			// NewLocation = Location + K * Direction
			// Find K such that Location.Z + K * Direction.Z = DrivingComponent->GetComponentLocation().Z
			auto K = (DrivingComponent->GetComponentLocation().Z - Location.Z) / Direction.Z;

			DrivingComponent->SetWorldLocation(Location + K * Direction);

			ManipulatorComponent->UpdateParametricMesh(DrivingComponent);
		}
		else if (bDragging)
		{
			auto HitPosition = Location + HitDistance * Direction;
			auto HitActor = HitComponent->GetAttachmentRootActor();
			auto HitActorLocation = HitActor->GetActorLocation();
			
			// NewLocation = Location + K * Direction
			// Find K such that Location.Z + K * Direction.Z = InitialHitLocation.Z
			auto K = (HitLocation.Z - Location.Z) / Direction.Z;

			HitActor->SetActorLocation(Location + K * Direction - DragDelta);
		}
	}
}

void AMousePawn::OnRelease()
{
	bGrabbing = false;
	HitComponent = nullptr;
	HitDistance = 0.f;
}

void AMousePawn::StartDrag()
{
	bCameraDragging = true;
}

void AMousePawn::StopDrag()
{
	bCameraDragging = false;
}

void AMousePawn::Yaw(float value)
{
	if (bCameraDragging)
		this->AddControllerYawInput(value);
}

void AMousePawn::Pitch(float value)
{
	if (bCameraDragging)
		this->AddControllerPitchInput(value);
}
