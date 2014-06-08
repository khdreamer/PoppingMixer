//
//  PoppingMixerViewController.m
//  PoppingMixer
//
//  Created by Kevin Huang on 2014/6/3.
//  Copyright (c) 2014年 NMLab Project. All rights reserved.
//

#import "PoppingMixerViewController.h"
#import "AudioModel.h"
#import "TheAmazingAudioEngine.h"

@interface PoppingMixerViewController ()

@property (nonatomic, strong) AudioModel *audioModel;
@property (nonatomic, strong) AEAudioController *audioController;
@property (nonatomic, strong) AEAudioFilePlayer *background;
@property (nonatomic, strong) AEAudioUnitFilter *reverb;

@end

@implementation PoppingMixerViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    [self addAudioController];
    [self playBackgroundMusic];
    [self addReverb];
    
}

- (void)addAudioController {

    self.audioController = [[AEAudioController alloc]
                            initWithAudioDescription:[AEAudioController nonInterleaved16BitStereoAudioDescription]
                            inputEnabled:YES];
    NSError *error = NULL;
    BOOL result = [self.audioController start:&error];
    if ( !result ) {
        // Report error
    }

}

- (void)playBackgroundMusic {
    
    NSURL *file = [[NSBundle mainBundle] URLForResource:@"track" withExtension:@"mp3"];
    self.background = [AEAudioFilePlayer audioFilePlayerWithURL:file
                                                audioController:_audioController
                                                          error:NULL];
    [_audioController addChannels:@[_background]];

}

- (void)addReverb {
    
    AudioComponentDescription component = AEAudioComponentDescriptionMake(kAudioUnitManufacturer_Apple,
                                                                          kAudioUnitType_Effect,
                                                                          kAudioUnitSubType_Reverb2);
    NSError *error = NULL;
    self.reverb = [[AEAudioUnitFilter alloc]
                   initWithComponentDescription:component
                   audioController:_audioController
                   error:&error];
    AudioUnitSetParameter(_reverb.audioUnit,
                          kReverb2Param_DryWetMix,
                          kAudioUnitScope_Global,
                          0,
                          self.reverbSlider.value,
                          0);
    if ( !_reverb ) {
        // Report error
    }
    [self.audioController addFilter:self.reverb];


}


- (AudioModel *)audioModel {
    
    if(!_audioModel){
        
        _audioModel = [[AudioModel alloc] init];
        
    }
    return _audioModel;
    
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)addBeat:(id)sender {
    
    NSLog(@"add beat");
    [self.audioModel playNote:24 withGain:200];
    
}

- (IBAction)applyReverb:(UISlider *)sender {
    
    AudioUnitSetParameter(_reverb.audioUnit,
                          kReverb2Param_DryWetMix,
                          kAudioUnitScope_Global,
                          0,
                          sender.value,
                          0);
    
}

@end
