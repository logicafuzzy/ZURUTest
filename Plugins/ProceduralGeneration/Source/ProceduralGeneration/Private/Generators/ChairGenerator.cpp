#include "Generators/ChairGenerator.h"
#include "Generators/GridBoxMeshGenerator.h"
#include "Generators/MeshGeneratorUtils.h"

FChairGenerator::FChairGenerator()
	: width(1.0f)
	, length(1.0f)
	, height(1.0f)
	, topThickness(1.0f)
	, legThickness(1.0f)
	, backHeight(1.0f)
{
	
}

FMeshShapeGenerator& FChairGenerator::Generate()
{
	Reset();

	//half dimensions
	const float hW = width / 2.0f;
	const float hL = length / 2.0f;
	const float hH = height / 2.0f;
	const float hTTop = topThickness / 2.0f;
	const float hTLeg = legThickness / 2.0f;
	const float hHLeg = (height - topThickness) / 2.0f;
	const float hB = backHeight / 2.0f;

	//TOP
	FGridBoxMeshGenerator GridBoxMeshGenerator;
	GridBoxMeshGenerator.bScaleUVByAspectRatio = false;
	//Gridbox has origin in the center and has 2x box extent size
	GridBoxMeshGenerator.Box = FOrientedBox3d({ hW, hL, height - hTTop }, { hW, hL, hTTop });
	MeshGeneratorUtils::MergeGeneratedMesh(GridBoxMeshGenerator.Generate(), *this);
	
	//Legs
	auto legSize = FVector(hTLeg, hTLeg, hH - hTTop);

	GridBoxMeshGenerator.Box = FOrientedBox3d({ hTLeg, hTLeg, hHLeg}, legSize);
	MeshGeneratorUtils::MergeGeneratedMesh(GridBoxMeshGenerator.Generate(), *this);

	GridBoxMeshGenerator.Box = FOrientedBox3d({ width - hTLeg, hTLeg, hHLeg}, legSize);
	MeshGeneratorUtils::MergeGeneratedMesh(GridBoxMeshGenerator.Generate(), *this);

	GridBoxMeshGenerator.Box = FOrientedBox3d({ hTLeg, length - hTLeg, hHLeg}, legSize);
	MeshGeneratorUtils::MergeGeneratedMesh(GridBoxMeshGenerator.Generate(), *this);

	GridBoxMeshGenerator.Box = FOrientedBox3d({ width - hTLeg, length - hTLeg, hHLeg}, legSize);
	MeshGeneratorUtils::MergeGeneratedMesh(GridBoxMeshGenerator.Generate(), *this);

	//back
	auto backSize = FVector(hW, hTLeg, hB);
	GridBoxMeshGenerator.Box = FOrientedBox3d({ hW, hL, hB}, backSize);
	MeshGeneratorUtils::MergeGeneratedMesh(GridBoxMeshGenerator.Generate(), *this);

	return *this;
}
