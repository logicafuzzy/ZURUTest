#include "Generators/TableGenerator.h"
#include "Generators/GridBoxMeshGenerator.h"

FTableGenerator::FTableGenerator()
{
}

FMeshShapeGenerator & FTableGenerator::Generate()
{
	this->temp = this->temp == nullptr ? new FGridBoxMeshGenerator() : this->temp;
	return this->temp->Generate();
}
