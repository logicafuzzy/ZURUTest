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
	SpringArmComponent->CameraLagSpeed = 5.0f;
	SpringArmComponent->CameraRotationLagSpeed = 5.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
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

		auto NewLocation = Location + HitDistance * Direction;
		NewLocation.Z = DrivingComponent->GetComponentLocation().Z;

		DrivingComponent->SetWorldLocation(NewLocation);

		ManipulatorComponent->UpdateParametricMesh(DrivingComponent);
	}
	else if (bCameraDragging)
	{

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
