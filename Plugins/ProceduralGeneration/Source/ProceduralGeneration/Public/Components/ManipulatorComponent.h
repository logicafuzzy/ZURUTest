#pragma once

#include "CoreMinimal.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ParametricMeshComponent.h"

#include "ManipulatorComponent.generated.h"

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALGENERATION_API UManipulatorComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UManipulatorComponent();

	UPROPERTY()
	UStaticMeshComponent* OriginComponent;

	UPROPERTY()
	UStaticMeshComponent* CornerComponent;
	
	UPROPERTY()
	UStaticMeshComponent* BottomRightComponent;
	
	UPROPERTY()
	UStaticMeshComponent* TopLeftComponent;

	void SetParametricMesh(UParametricMeshComponent* ParametricMeshComponent);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = StrategyParamNames)
	FName OriginParamName;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = StrategyParamNames)
	FName CornerParamName;

private:
	UParametricMeshComponent* ParametricMeshComponent;
};