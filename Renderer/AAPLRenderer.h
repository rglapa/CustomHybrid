//
//  Untitled.swift
//  CustomHybrid
//
//  Created by Ruben Glapa on 3/25/25.
//

#import <MetalKit/MetalKit.h>

typedef NS_ENUM(uint8_t, RenderMode )
{
    RMNoRaytracing = 0,
    RMMetalRaytracing = 1,
    RMReflectionsOnly = 2
};

// The platform-independent renderer class. Implements the MTKViewDelegate protocol, which
// allows it to accept per-frame update and drawable resize callbacks.
@interface AAPLRenderer: NSObject <MTKViewDelegate>
- (nonnull instancetype)initWithMetalKitView:(nonnull MTKView *)view size:(CGSize)size;
- (void)setRenderMode:(RenderMode)renderMode;
- (void)setCameraPanSpeedFactor:(float)speedFactor;
- (void)setMetallicBias:(float)metallicBias;
- (void)setRoughnessBias:(float)roughnessBias;
- (void)setExposure:(float)exposure;

@end
