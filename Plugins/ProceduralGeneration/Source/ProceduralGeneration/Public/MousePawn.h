#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "MousePawn.generated.h"

UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALGENERATION_API AMousePawn : public APawn
{
	GENERATED_BODY()

public:

	AMousePawn();

	virtual void Tick(float deltatime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName FloorTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName TableTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> ActorClassToSpawn;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

protected:

private:
	UPROPERTY()
	UPrimitiveComponent* HitComponent;

	bool bGrabbing;
	bool bDragging;

	float HitDistance;

	bool bCameraDragging;
	bool bCameraPanning;
	
	//initial delta when dragging starts
	FVector DragDelta;
	FVector HitLocation;

	UFUNCTION()
	void OnClick();

	UFUNCTION()
	void OnRelease();

	UFUNCTION()
	void StartDrag();

	UFUNCTION()
	void StopDrag();	
	
	UFUNCTION()
	void StartPan();

	UFUNCTION()
	void StopPan();

	UFUNCTION()
	void Yaw(float value);

	UFUNCTION()
	void Pitch(float value);

	UFUNCTION()
	void Zoom(float value);

	UFUNCTION()
	void Quit();


};