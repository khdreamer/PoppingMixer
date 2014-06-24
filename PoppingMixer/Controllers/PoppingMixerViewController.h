//
//  PoppingMixerViewController.h
//  PoppingMixer
//
//  Created by Kevin Huang on 2014/6/3.
//  Copyright (c) 2014年 NMLab Project. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BLE.h"

@interface PoppingMixerViewController : UIViewController <BLEDelegate>

@property (weak, nonatomic) IBOutlet UIButton *touchMeButton;
@property (weak, nonatomic) IBOutlet UISlider *reverbSlider;
@property (weak, nonatomic) IBOutlet UISlider *lowpassSlider;
@property (weak, nonatomic) IBOutlet UISlider *pitchShiftSlider;
@property (weak, nonatomic) IBOutlet UISlider *delaySlider;
@property (weak, nonatomic) IBOutlet UISlider *highpassSlider;
@property (strong, nonatomic) BLE* ble;



- (IBAction)addBeat:(id)sender;
- (IBAction)playBackground:(id)sender;
- (IBAction)applyReverb:(UISlider *)sender;
- (IBAction)addLowpass:(UISlider *)sender;
- (IBAction)changePitch:(UISlider *)sender;
- (IBAction)changeDelay:(UISlider *)sender;
- (IBAction)addHighPass:(UISlider *)sender;

@end
