//
//  ViewController.m
//  CustomHybrid
//
//  Created by Ruben Glapa on 3/25/25.
//

#import "ViewController.h"
#import "../Renderer/AAPLRenderer.h"

@implementation ViewController
{
    MTKView *_view;
    
    AAPLRenderer *_renderer;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end
