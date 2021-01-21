#include "Generators/ParametricChairGenerator.h"
#include "ProceduralGenerationModule.h"

FParametricChairGenerator::FParametricChairGenerator()
	: FParametricGenerator(new FChairGenerator())
	, WidthParamName(TEXT("Width"))
	, LengthParamName(TEXT("Length"))
	, HeightParamName(TEXT("Height"))
	, BackHeightParamName(TEXT("BackHeight"))
{
	ChairGenerator = static_cast<FChairGenerator*>(this->DecoratedMeshShapeGenerator);

	ChairGenerator->height = 55.0f;
	ChairGenerator->width = 55.0f;
	ChairGenerator->legThickness = 5.0f;
	ChairGenerator->topThickness = 3.0f;
	ChairGenerator->backHeight = 45.0f;
}

FMeshShapeGenerator& FParametricChairGenerator::Generate()
{
	if (MeshParams.ScalarParams.Contains(WidthParamName))
		ChairGenerator->width = *MeshParams.ScalarParams.Find(WidthParamName);
	
	if (MeshParams.ScalarParams.Contains(LengthParamName))
		ChairGenerator->length = *MeshParams.ScalarParams.Find(LengthParamName);

	if (MeshParams.ScalarParams.Contains(HeightParamName))
		ChairGenerator->height = *MeshParams.ScalarParams.Find(HeightParamName);

	if (MeshParams.ScalarParams.Contains(HeightParamName))
		ChairGenerator->backHeight = *MeshParams.ScalarParams.Find(BackHeightParamName);

	return FParametricGenerator::Generate();
}
