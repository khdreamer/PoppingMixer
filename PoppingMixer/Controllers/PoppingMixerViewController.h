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
@property (weak, nonatomic) IBOutlet UISlider *delayFeedbackSlider;
@property (weak, nonatomic) IBOutlet UISlider *delayWetSlider;
@property (weak, nonatomic) IBOutlet UISlider *delayTimeSlider;
@property (weak, nonatomic) IBOutlet UISlider *highpassSlider;
@property (strong, nonatomic) BLE* ble;
@property (weak, nonatomic) IBOutlet UIButton *acapellaButton;
@property (weak, nonatomic) IBOutlet UIButton *instrumentalButton;


- (IBAction)connect:(id)sender;

- (IBAction)toggleChannel:(UISwitch *)sender;
- (IBAction)selectChannel:(UIButton *)sender;

- (IBAction)addBeat:(id)sender;
- (IBAction)playBackground:(id)sender;
- (IBAction)applyReverb:(UISlider *)sender;
- (IBAction)addLowpass:(UISlider *)sender;
- (IBAction)changePitch:(UISlider *)sender;
- (IBAction)addHighPass:(UISlider *)sender;
- (IBAction)changeDelayWet:(UISlider *)sender;
- (IBAction)changeDelayTime:(UISlider *)sender;
- (IBAction)changeDelayFeedback:(UISlider *)sender;

@end
