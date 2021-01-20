#pragma once

#include "CoreMinimal.h"
#include "Generators/MeshShapeGenerator.h"

namespace MeshGeneratorUtils	 
{
	PROCEDURALGENERATION_API void MergeGeneratedMesh(FMeshShapeGenerator& Source, FMeshShapeGenerator& Dest);
}