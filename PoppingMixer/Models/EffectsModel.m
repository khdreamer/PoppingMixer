//
//  EffectsModel.m
//  PoppingMixer
//
//  Created by Kevin Huang on 2014/6/24.
//  Copyright (c) 2014年 NMLab Project. All rights reserved.
//

#import "EffectsModel.h"
#import "TheAmazingAudioEngine.h"

@interface EffectsModel()

@property (nonatomic) BOOL isPlaying;

// effects
@property (nonatomic, strong) AEAudioUnitFilter *reverb;
@property (nonatomic, strong) AEAudioUnitFilter *lowpass;
@property (nonatomic, strong) AEAudioUnitFilter *changePitch;
@property (nonatomic, strong) AEAudioUnitFilter *changeSpeed;

// basis
@property (nonatomic, strong) AEAudioFilePlayer *background;
@property (nonatomic, strong) AEAudioController *audioController;

@end

@implementation EffectsModel

- (id)init {
    
    self = [super init];
    if (!self) {
        return nil;
    }
    
    _isPlaying = NO;
    
    return self;
    
}

#pragma basis

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

#pragma init fx

- (void)togglePlaying {

    if(!self.isPlaying){
    
        [self playBackgroundMusic];
        self.isPlaying = YES;
    
    }

}

- (void)initEffects {

    [self addReverb:0];
    [self addLowpass:100000];
    [self addPitchShift:1];

}

- (void)addReverb:(float)value {
    
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
                          value,
                          0);
    if ( !_reverb ) {
        // Report error
    }
    [self.audioController addFilter:self.reverb];
    
    
}

- (void)addLowpass:(float)value {
    
    AudioComponentDescription component = AEAudioComponentDescriptionMake(kAudioUnitManufacturer_Apple,
                                                                          kAudioUnitType_Effect,
                                                                          kAudioUnitSubType_LowPassFilter);
    NSError *error = NULL;
    self.lowpass = [[AEAudioUnitFilter alloc]
                   initWithComponentDescription:component
                   audioController:_audioController
                   error:&error];
    AudioUnitSetParameter(_lowpass.audioUnit,
                          kLowPassParam_CutoffFrequency,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    if ( !_lowpass ) {
        // Report error
    }
    [self.audioController addFilter:self.lowpass];
    
    
}


- (void)addPitchShift:(float)value {
    
    // adjust pitch
    AudioComponentDescription component = AEAudioComponentDescriptionMake(kAudioUnitManufacturer_Apple,
                                                                          kAudioUnitType_Effect,
                                                                          kAudioUnitSubType_NewTimePitch);
    NSError *error = NULL;
    self.changePitch = [[AEAudioUnitFilter alloc]
                      initWithComponentDescription:component
                      audioController:_audioController
                      error:&error];
    AudioUnitSetParameter(_changePitch.audioUnit,
                          kNewTimePitchParam_Pitch,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    
    if ( !_changePitch ) {
        // Report error
    }
    [self.audioController addFilter:self.changePitch];
    
}


#pragma change value

- (void)changeReverbValue:(float)value {

    AudioUnitSetParameter(_reverb.audioUnit,
                          kReverb2Param_DryWetMix,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);

}

- (void)changeLowpassValue:(float)value {
    
    AudioUnitSetParameter(_lowpass.audioUnit,
                          kLowPassParam_CutoffFrequency,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    
}

- (void)changePitchWithPitch:(float)value {
    
    AudioUnitSetParameter(_changePitch.audioUnit,
                          kNewTimePitchParam_Pitch,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    
}

@end
