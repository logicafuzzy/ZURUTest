#pragma once

#include "CoreMinimal.h"
#include "Components/ParametricMeshComponent.h"

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
	UParametricMeshComponent* UManipulatorComponent;

	virtual void OnConstruction(const FTransform& Transform) override;

protected:

private:

};