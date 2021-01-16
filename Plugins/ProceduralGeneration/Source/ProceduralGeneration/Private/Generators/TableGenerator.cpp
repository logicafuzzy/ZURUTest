#include "Generators/TableGenerator.h"
#include "Generators/SphereGenerator.h"

FTableGenerator::FTableGenerator()
{
	auto temp_ = new FSphereGenerator();
	temp_->Radius = 50.0f;
	this->temp = temp_;
}

FMeshShapeGenerator & FTableGenerator::Generate()
{
	return this->temp->Generate();
}
