#pragma once

#include "CoreMinimal.h"
#include "Components/ParametricMeshComponent.h"
#include "Components/ManipulatorComponent.h"

#include "ResizableTable.generated.h"

UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALGENERATION_API AResizableTable : public AActor
{
	GENERATED_BODY()

public:

	AResizableTable();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UParametricMeshComponent* ResizableMeshComponent;


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UManipulatorComponent* ManipulatorComponent;

	virtual void OnConstruction(const FTransform& Transform) override;

protected:

private:

};