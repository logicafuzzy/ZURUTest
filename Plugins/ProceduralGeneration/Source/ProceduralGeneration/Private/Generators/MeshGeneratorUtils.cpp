#include "Generators/MeshGeneratorUtils.h"

#include "MeshDescription.h"
#include "StaticMeshAttributes.h"
#include "DynamicMeshToMeshDescription.h"

void MeshGeneratorUtils::MergeGeneratedMesh(FMeshShapeGenerator& Source, FMeshShapeGenerator& Dest)
{

	//Vertex index offset
	const auto nVertices = Dest.Vertices.Num();
	const auto nUVs = Dest.UVs.Num();
	const auto nNormals = Dest.Normals.Num();
	const auto nTriangles = Dest.Triangles.Num();

	//Prealloc memory
	Dest.Vertices.Reserve(Source.Vertices.Num() + nVertices);
	Dest.UVs.Reserve(Source.UVs.Num() + nUVs);
	Dest.UVParentVertex.Reserve(Source.UVParentVertex.Num() + nUVs);
	Dest.Normals.Reserve(Source.Normals.Num() + nNormals);
	Dest.NormalParentVertex.Reserve(Source.NormalParentVertex.Num() + nNormals);
	Dest.Triangles.Reserve(Source.Triangles.Num() + nTriangles);
	Dest.TriangleUVs.Reserve(Source.TriangleUVs.Num() + nTriangles);
	Dest.TriangleNormals.Reserve(Source.TriangleNormals.Num() + nTriangles);
	Dest.TrianglePolygonIDs.Reserve(Source.TrianglePolygonIDs.Num() + nTriangles);

	///** Array of vertex positions */
	Dest.Vertices.Append(Source.Vertices);

	///** Array of UV positions. These are completely independent of vertex list (ie not per-vertex unless that's what generator produces) */
	Dest.UVs.Append(Source.UVs);

	///** Parent vertex index for each UV. Same length as UVs array. */
	for (auto UVParentVertexIndex : Source.UVParentVertex)
	{
		Dest.UVParentVertex.Add(UVParentVertexIndex + nVertices);
	}

	///** Array of Normals. These are completely independent of vertex list (ie not per-vertex unless that's what generator produces) */
	Dest.Normals.Append(Source.Normals);

	///** Parent vertex index for each Normal. Same length as Normals array. */
	for (auto NormalParentVertexIndex : Source.NormalParentVertex)
	{
		Dest.NormalParentVertex.Add(NormalParentVertexIndex + nVertices);
	}

	///** Array of triangle corner positions, stored as tuples of indices into Vertices array */
	for (auto Triangle : Source.Triangles)
	{
		Triangle.A += nVertices;
		Triangle.B += nVertices;
		Triangle.C += nVertices;

		Dest.Triangles.Add(Triangle);
	}

	///** Array of triangle corner UVs, stored as tuples of indices into UVs array. Same length as Triangles array. */
	for (auto TriangleUV : Source.TriangleUVs)
	{
		TriangleUV.A += nUVs;
		TriangleUV.B += nUVs;
		TriangleUV.C += nUVs;
		Dest.TriangleUVs.Add(TriangleUV);
	}
	///** Array of triangle corner Normals, stored as tuples of indices into Normals array. Same length as Triangles array. */
	for (auto TriangleNormal : Source.TriangleNormals)
	{
		TriangleNormal.A += nNormals;
		TriangleNormal.B += nNormals;
		TriangleNormal.C += nNormals;
		Dest.TriangleNormals.Add(TriangleNormal);
	}
	///** Array of per-triangle integer polygon IDs. Same length as Triangles array. */
	//TArray<int> TrianglePolygonIDs;
	for (auto TrianglePolygonID : Source.TrianglePolygonIDs)
	{
		Dest.TrianglePolygonIDs.Add(TrianglePolygonID + nTriangles);
	}

}

PROCEDURALGENERATION_API UStaticMesh * MeshGeneratorUtils::UpdateStaticMesh(FMeshShapeGenerator* Source, UStaticMesh* StaticMesh, FDynamicMesh3& DynamicMesh)
{
	DynamicMesh.Copy(&Source->Generate());

	FMeshDescription MeshDescription;
	FStaticMeshAttributes StaticMeshAttributes(MeshDescription);
	StaticMeshAttributes.Register();

	FDynamicMeshToMeshDescription Converter;
	Converter.Convert(&DynamicMesh, MeshDescription);

	// todo: vertex color support

	//UStaticMesh* StaticMesh = NewObject<UStaticMesh>(Component);
	//FName MaterialSlotName = StaticMesh->AddMaterial(MyMaterial);

	// Build the static mesh render data, one FMeshDescription* per LOD.
	TArray<const FMeshDescription*> MeshDescriptionPtrs;
	MeshDescriptionPtrs.Emplace(&MeshDescription);
	StaticMesh->BuildFromMeshDescriptions(MeshDescriptionPtrs);
	return StaticMesh;
}
