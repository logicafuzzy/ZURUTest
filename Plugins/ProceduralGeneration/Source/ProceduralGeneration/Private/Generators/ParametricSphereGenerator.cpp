#include "Generators/ParametricSphereGenerator.h"

#include "Generators/SphereGenerator.h"

FParametricSphereGenerator::FParametricSphereGenerator()
	: FParametricGenerator(new FSphereGenerator())
{
	SphereGenerator = (FSphereGenerator*)DecoratedMeshShapeGenerator;
}

FMeshShapeGenerator& FParametricSphereGenerator::Generate()
{
	SphereGenerator->Radius = this->MeshParams.ScalarParams.Contains(RadiusParamName) ? *this->MeshParams.ScalarParams.Find(RadiusParamName) : 10.0f;

	return this->DecoratedMeshShapeGenerator->Generate();
}