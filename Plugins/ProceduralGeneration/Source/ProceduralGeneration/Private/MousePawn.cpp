#include "MousePawn.h" 

#include "ProceduralGenerationModule.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "ResizableTable.h"

AMousePawn::AMousePawn()
	: FloorTag(TEXT("Floor"))
	, ActorClassToSpawn(AResizableTable::StaticClass())
{
	auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController != nullptr)
	{
		PlayerController->bEnableClickEvents = true;
		PlayerController->bShowMouseCursor = true;
		PlayerController->InputComponent->BindAction("MouseLeftClicked", IE_Pressed, this, &AMousePawn::OnClick);
	}
	else
	{
		UE_LOG(ProceduralGenerationLog, Error, TEXT("PlayerController is nullptr"));
	}
}

void AMousePawn::OnClick()
{
	auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	FVector Location, Direction;

	PlayerController->DeprojectMousePositionToWorld(Location, Direction);

	FHitResult Hit;

	UKismetSystemLibrary::LineTraceSingle(this, Location, Location + 10000.0f*Direction, ETraceTypeQuery::TraceTypeQuery1 , false, TArray<AActor*>(), EDrawDebugTrace::Persistent, Hit, true);

	auto HitComponent = Hit.GetComponent();

	if (HitComponent)
	{
		if (HitComponent->ComponentHasTag(FloorTag))
		{
			this->GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, Hit.Location, HitComponent->GetComponentRotation());
		}
		UE_LOG(ProceduralGenerationLog, Display, TEXT("Hit %s"), *HitComponent->GetFName().ToString());
	}

	UE_LOG(ProceduralGenerationLog, Display, TEXT("Click"));
}