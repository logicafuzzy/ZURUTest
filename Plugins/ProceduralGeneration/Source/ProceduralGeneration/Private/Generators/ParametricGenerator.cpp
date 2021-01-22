#include "Generators/ParametricGenerator.h"

FParametricGenerator::FParametricGenerator(FMeshShapeGenerator* MeshShapeGenerator)
{
	ensure(MeshShapeGenerator != nullptr && "Generator can't be null");

	this->DecoratedMeshShapeGenerator = MeshShapeGenerator;
}

FParametricGenerator::~FParametricGenerator()
{
	delete this->DecoratedMeshShapeGenerator;
}


FMeshShapeGenerator& FParametricGenerator::Generate()
{
	return this->DecoratedMeshShapeGenerator->Generate();
}