#include "Generators/ParametricSphereGenerator.h"

#include "Generators/SphereGenerator.h"

FParametricSphereGenerator::FParametricSphereGenerator()
	: FParametricGenerator(new FSphereGenerator())
{
	SphereGenerator = (FSphereGenerator*)DecoratedMeshShapeGenerator;
}

FMeshShapeGenerator& FParametricSphereGenerator::Generate()
{
	auto Radius = this->MeshParams.ScalarParams.Find(FName(TEXT("Radius")));

	SphereGenerator->Radius = Radius ? *Radius : 1.0f;

	return this->DecoratedMeshShapeGenerator->Generate();
}