#include "MousePawn.h" 

#include "ProceduralGenerationModule.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

AMousePawn::AMousePawn()
{
	auto PlayerController = UGameplayStatics::GetPlayerController(GetOwner(), 0);

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

}