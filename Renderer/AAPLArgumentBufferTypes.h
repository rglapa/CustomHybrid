//
//  AAPLArgumentBufferTypes.h
//  CustomHybrid
//
//  Created by Ruben Glapa on 3/25/25.
//

#ifndef AAPLArgumentBufferTypes_h
#define AAPLArgumentBufferTypes_h

#include "AAPLShaderTypes.h"

typedef enum AAPLArgumentBufferID
{
    AAPLArgumentBufferIDGenericsTexcoord,
    AAPLArgumentBufferIDGenericsNormal,
    AAPLArgumentBufferIDGenericsTangent,
    AAPLArgumentBufferIDGenericsBitangent,
    
    AAPLArgumentBufferIDSubmeshIndices,
    AAPLArgumentBufferIDSubmeshMaterials,
    
    AAPLArgumentBufferIDMeshPositions,
    AAPLArgumentBufferIDMeshGenerics,
    AAPLArgumentBufferIDMeshSubmeshes,
    
    AAPLArgumentBufferIDInstanceMesh,
    AAPLArgumentBufferIDInstanceTransform,
    
    AAPLArgumentBufferIDSceneInstances,
    AAPLArgumentBufferIDSceneMeshes
} AAPLArgumentBufferID;

#if __METAL_VERSION__

#include <metal_stdlib>
using namespace metal;

struct MeshGenerics
{
    float2 texcoord [[ id(AAPLArgumentBufferIDGenericsTexcoord)]];
    half4 normal    [[ id(AAPLArgumentBufferIDGenericsNormal)]];
    half4 tangent   [[ id(AAPLArgumentBufferIDGenericsTangent)]];
    half4 bitangent [[ id(AAPLArgumentBufferIDGenericsBitangent)]];
};

struct Submesh
{
    // The container mesh stores positions and generic vertex attribute arrays.
    // The submesh stores only indices into these vertex arrays.
    uint32_t shortIndexType [[id(0)]];
    
    // The indices for the container mesh's position and generics arrays.
    constant uint32_t*                 indices    [[id(AAPLArgumentBufferIDSubmeshIndices)]];
    
    // The fixed size array of material textures.
    array<texture2d<float>, AAPLMaterialTextureCount> materials [[id(AAPLArgumentBufferIDSubmeshMaterials)]];
};

struct Mesh
{
    // The arrays of vertices.
    constant packed_float3* positions [[id(AAPLArgumentBufferIDMeshPositions)]];
    constant MeshGenerics* generics [[id(AAPLArgumentBufferIDMeshGenerics)]];
    
    // The array of submeshes.
    constant Submesh* submeshes   [[id(AAPLArgumentBufferIDMeshSubmeshes)]];
};

struct Instance
{
    // A reference to a single mesh in the meshes array stored in structure `Scene`.
    uint32_t meshIndex [[id(0)]];
    // constant Mesh* pMesh [[id(AAPLArgumentBufferIDInstanceMesh)]];
    
    // The location of the mesh for this instance.
    float4x4 transform [[id(1)]];
};

struct Scene
{
    // The array of instances.
    constant Instance* instances [[id(AAPLArgumentBufferIDSceneInstances)]];
    constant Mesh* meshes [[id(AAPLArgumentBufferIDSceneMeshes)]];
};

#else

#include <Metal/Metal.h>

struct Submesh
{
    // The container mesh stores positions and generic vertex attribute arrays.
    // The submesh stores only indices in these vertex arrays.
    
    uint32_t shortIndexType;
    
    // Indices for the container mesh's position and generics arrays.
    uint64_t indices;
    
    // The fixed size array of material textures.
    MTLResourceID materials[AAPLMaterialTextureCount];
};

struct Mesh
{
    // The array of vertices.
    uint64_t positions;
    uint64_t generics;
    
    // The array of submeshes.
    uint64_t submeshes;
};

struct Instance
{
    // A reference to a single mesh.
    uint32_t meshIndex;
    
    // The location of the mesh for this instance.
    matrix_float4x4 transform;
};

struct Scene
{
    // The array of instances.
    uint64_t instances;
    uint64_t meshes;
};
#endif // __METAL_VERSION__

#endif // AAPLArgumentBufferTypes_h

