#pragma once

#include "CoreMinimal.h"
#include "Components/ParametricMeshComponent.h"
#include "Components/ManipulatorComponent.h"
#include "Components/InstanceGeneratorComponent.h"

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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UInstanceGeneratorComponent* ChairFrontRow;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UInstanceGeneratorComponent * ChairBackRow;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UInstanceGeneratorComponent * ChairLeftRow;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UInstanceGeneratorComponent * ChairRightRow;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FMeshParams ChairMeshParams;
	
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	UPROPERTY()
	TArray<UParametricMeshComponent*> ChairInstanceComponents;
private:

	UFUNCTION()
	void OnUpdateMesh(const FMeshParams& MeshParams);
};