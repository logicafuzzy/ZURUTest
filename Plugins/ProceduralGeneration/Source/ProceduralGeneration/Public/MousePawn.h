#pragma once

#include "CoreMinimal.h"

#include "MousePawn.generated.h"

UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALGENERATION_API AMousePawn : public APawn
{
	GENERATED_BODY()

public:

	AMousePawn();

	UFUNCTION()
	void OnClick();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName FloorTag;
protected:

private:

};