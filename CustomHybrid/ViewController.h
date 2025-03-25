//
//  ViewController.h
//  CustomHybrid
//
//  Created by Ruben Glapa on 3/25/25.
//

#import <AppKit/AppKit.h>

@interface ViewController : NSViewController

@property (nonatomic, weak) IBOutlet NSSegmentedControl* renderModeControl;
@property (nonatomic, weak) IBOutlet NSSlider* speedSlider;
@property (nonatomic, weak) IBOutlet NSSlider* metallicBiasSlider;
@property (nonatomic, weak) IBOutlet NSSlider* roughnessBiasSlider;
@property (nonatomic, weak) IBOutlet NSSlider* exposureSlider;
@property (nonatomic, weak) IBOutlet NSView* configBackdrop;
@property (nonatomic, weak) IBOutlet NSProgressIndicator* loadingSpinner;
@property (nonatomic, weak) IBOutlet NSTextField* loadingLabel;

- (IBAction)onRenderModeSegmentedControlAction:(id)sender;
- (IBAction)onSpeedSliderAction:(id)sender;
- (IBAction)onMetallicBiasAction:(id)sender;
- (IBAction)onRoughnessBiasAction:(id)sender;
- (IBAction)onExposureSliderAction:(id)sender;

@end

