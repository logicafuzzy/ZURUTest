#pragma once

#include "CoreMinimal.h"
#include "Generators/MeshShapeGenerator.h"

#include "DynamicMesh3.h"

namespace MeshGeneratorUtils	 
{
	PROCEDURALGENERATION_API void MergeGeneratedMesh(FMeshShapeGenerator& Source, FMeshShapeGenerator& Dest);

	//take it out from ParametriMEshComponent
	PROCEDURALGENERATION_API UStaticMesh* UpdateStaticMesh(FMeshShapeGenerator* Source, UStaticMesh* StaticMesh, FDynamicMesh3& DynamicMesh, bool bBuildCollision);
}