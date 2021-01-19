#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"

#include "MousePawn.generated.h"

UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALGENERATION_API AMousePawn : public APawn
{
	GENERATED_BODY()

public:

	AMousePawn();

	UFUNCTION()
	void OnClick();
	
	UFUNCTION()
	void OnRelease();

	virtual void Tick(float deltatime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName FloorTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> ActorClassToSpawn;

protected:

private:
	UPROPERTY()
	UPrimitiveComponent* HitComponent;

	bool bGrabbing;
	float HitDistance;

};