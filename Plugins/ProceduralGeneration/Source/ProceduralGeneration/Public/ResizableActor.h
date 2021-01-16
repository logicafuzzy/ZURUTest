#pragma once

#include "CoreMinimal.h"
#include "Components/ParametricMeshComponent.h"


#include "ResizableActor.generated.h"

UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALGENERATION_API AResizableActor : public AActor
{
	GENERATED_BODY()

public:

	AResizableActor();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UParametricMeshComponent* ResizableMeshComponent;

	virtual void OnConstruction(const FTransform& Transform) override;

protected:

private:

};