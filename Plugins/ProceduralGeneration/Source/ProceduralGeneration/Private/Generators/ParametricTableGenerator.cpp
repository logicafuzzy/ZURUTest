#include "Generators/ParametricTableGenerator.h"
#include "ProceduralGenerationModule.h"

FParametricTableGenerator::FParametricTableGenerator()
	: FParametricGenerator(new FTableGenerator())
	, WidthParamName(TEXT("Width"))
	, LengthParamName(TEXT("Length"))
	, HeightParamName(TEXT("Height"))
{
	TableGenerator = static_cast<FTableGenerator*>(this->DecoratedMeshShapeGenerator);

	TableGenerator->height = 85.0f;
	TableGenerator->legThickness = 10.0f;
	TableGenerator->topThickness = 5.0f;
}

FMeshShapeGenerator& FParametricTableGenerator::Generate()
{
	if (MeshParams.ScalarParams.Contains(WidthParamName))
		TableGenerator->width = *MeshParams.ScalarParams.Find(WidthParamName);
	
	if (MeshParams.ScalarParams.Contains(LengthParamName))
		TableGenerator->length = *MeshParams.ScalarParams.Find(LengthParamName);

	if (MeshParams.ScalarParams.Contains(HeightParamName))
		TableGenerator->height = *MeshParams.ScalarParams.Find(HeightParamName);

	return FParametricGenerator::Generate();
}
