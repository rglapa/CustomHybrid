//
//  AAPLRenderer.m
//  CustomHybrid
//
//  Created by Ruben Glapa on 3/25/25.
//

#import <MetalPerformanceShaders/MetalPerformanceShaders.h>
#import <ModelIO/ModelIO.h>
#import "AAPLMathUtilities.h"

#import "AAPLRenderer.h"

#import "AAPLMesh.h"
#import "AAPLModelInstance.h"

/// Include the headers that share types between the C code here, which executes
/// Metal API commands, and the .metal files, which use the types as inputs to the shaders.
#import "AAPLShaderTypes.h"
#import "AAPLArgumentBufferTypes.h"

/// Controls whether to include Metal residency set functionality to the app.
/// The `MTLResidencySet` APIs require macOS 15 or later, or iOS 18 or later.
#if (TARGET_MACOS && defined(__MAC_15_0) && (__MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_15_0)) || \
    (TARGET_IOS && defined(__IPHONE_18_0) && (__IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_18_0))
    #define AAPL_SUPPORTS_RESIDENCY_SETS 1
#else
    #define AAPL_SUPPORTS_RESIDENCY_SETS 0
#endif

MTLPackedFloat4x3 matrix4x4_drop_last_row(matrix_float4x4 m)
{
    return (MTLPackedFloat4x3) {
        MTLPackedFloat3Make( m.columns[0].x, m.columns[0].y, m.columns[0].z ),
        MTLPackedFloat3Make( m.columns[1].x, m.columns[1].y, m.columns[1].z ),
        MTLPackedFloat3Make( m.columns[2].x, m.columns[2].y, m.columns[2].z ),
        MTLPackedFloat3Make( m.columns[3].x, m.columns[3].y, m.columns[3].z )
    };
}

static const NSUInteger kMaxBuffersInFlight = 3;

static const size_t kAlignedInstanceTransformsStructSize = (sizeof(AAPLInstanceTransform) & ~0xFF) + 0x100;

typedef enum AccelerationStructureEvents : uint64_t
{
    kPrimitiveAccelerationStructureBuild = 1,
    kInstanceAccelerationStructureBuild = 2
} AccelerationStructureEvents;

typedef struct ThinGBuffer
{
    id<MTLTexture> positionTexture;
    id<MTLTexture> directionTexture;
} ThinGBuffer;

/// A helper function that passes an array of instances into batch methods that require pointers and counts.
void arrayToBatchMethodHelper(NSArray *array, void (^callback)(__unsafe_unretained id *, NSUInteger))
{
    static const NSUInteger bufferLength = 16;
    __unsafe_unretained id buffer[bufferLength];
    NSFastEnumerationState state = {};
    
    NSUInteger count;
    
    while ((count = [array countByEnumeratingWithState:&state objects:buffer count:bufferLength]) > 0)
    {
        callback(state.itemsPtr, count);
    }
}

@implementation AAPLRenderer
{
    dispatch_semaphore_t _inFlightSemaphore;
    
    id<MTLDevice> _device;
    id<MTLCommandQueue> _commandQueue;
    
    id<MTLBuffer> _lightDataBuffer;
    id<MTLBuffer> _cameraDataBuffersr[kMaxBuffersInFlight];
    id<MTLBuffer> _instanceTransformBuffer;
    
    id<MTLRenderPipelineState> _pipelineState;
    id<MTLRenderPipelineState> _pipelineStateNoRT;
    id<MTLRenderPipelineState> _pipelineStateReflOnly;
    id<MTLRenderPipelineState> _gbufferPipelineState;
    id<MTLRenderPipelineState> _skyboxPipelineState;
    id<MTLDepthStencilState> _depthState;
    
    MTLVertexDescriptor *_mtlVertexDescriptor;
    MTLVertexDescriptor *_mtlSkyboxVertexDescriptor;
    
    uint8_t _cameraBufferIndex;
    matrix_float4x4 _projectionMatrix;
    
    NSArray<AAPLMesh *>* _meshes;
}

@end
