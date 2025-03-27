//
//  main.m
//  CustomHybrid
//
//  Created by Ruben Glapa on 3/25/25.
//

#if defined(TARGET_IOS)
#import <UIKit/UIKit.h>
#import <TargetConditionals.h>
#import <Availability.h>
#import "AppDelegate.h"
#else
#import <Cocoa/Cocoa.h>
#endif

#if defined(TARGET_IOS)

int main(int argc, char * argv[]) {
#if TARGET_OS_SIMULATOR
#error This sample does not support the iOS Simulator
#endif

    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AAPLAppDelegate class]));
    }
}
}
#elif defined(TARGET_MACOS)

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
    }
    return NSApplicationMain(argc, argv);
}

#endif
