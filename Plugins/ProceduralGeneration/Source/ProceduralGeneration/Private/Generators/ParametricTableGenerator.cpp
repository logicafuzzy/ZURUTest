#include "Generators/ParametricTableGenerator.h"

FParametricTableGenerator::FParametricTableGenerator()
	: FParametricGenerator(new FTableGenerator())
{

}

FMeshShapeGenerator& FParametricTableGenerator::Generate()
{
	return FParametricGenerator::Generate();
}
