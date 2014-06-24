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

@property (nonatomic) BOOL musicAdded;

// effects
@property (nonatomic, strong) AEAudioUnitFilter *reverb;
@property (nonatomic, strong) AEAudioUnitFilter *lowpass;
@property (nonatomic, strong) AEAudioUnitFilter *highpass;
@property (nonatomic, strong) AEAudioUnitFilter *changePitch;
@property (nonatomic, strong) AEAudioUnitFilter *changeSpeed;
@property (nonatomic, strong) AEAudioUnitFilter *delay;

// basis
@property (nonatomic, strong) AEAudioFilePlayer *instrumental;
@property (nonatomic, strong) AEAudioFilePlayer *acapella;
@property (nonatomic, strong) AEAudioController *audioController;

@end

@implementation EffectsModel

- (id)init {
    
    self = [super init];
    if (!self) {
        return nil;
    }
    
    _musicAdded = NO;
    
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

- (void)playMusic {
    
    NSURL *instrumentalMusic = [[NSBundle mainBundle] URLForResource:@"lies_and_misery_instrumental" withExtension:@"aif"];
    self.instrumental = [AEAudioFilePlayer audioFilePlayerWithURL:instrumentalMusic
                                                audioController:_audioController
                                                          error:NULL];
    NSURL *acapellaMusic = [[NSBundle mainBundle] URLForResource:@"lies_and_misery_acapella" withExtension:@"aif"];
    self.acapella = [AEAudioFilePlayer audioFilePlayerWithURL:acapellaMusic
                                                  audioController:_audioController
                                                            error:NULL];
    [_audioController addChannels:@[_instrumental, _acapella]];
    
}

#pragma init fx

- (void)togglePlaying {

    if(!self.musicAdded){
    
        [self playMusic];
        self.musicAdded = YES;
    
    }
    else {
    
        if(self.instrumental.channelIsPlaying) self.instrumental.channelIsPlaying = NO;
        else self.instrumental.channelIsPlaying = YES;
    
    }

}

- (void)initEffects {

    [self addReverb:0];
    [self addLowpass:100000];
    [self addPitchShift:1];
    [self addDelay:0];
    [self addHighpass:1];

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

- (void)addHighpass:(float)value {
    
    AudioComponentDescription component = AEAudioComponentDescriptionMake(kAudioUnitManufacturer_Apple,
                                                                          kAudioUnitType_Effect,
                                                                          kAudioUnitSubType_HighPassFilter);
    NSError *error = NULL;
    self.highpass = [[AEAudioUnitFilter alloc]
                    initWithComponentDescription:component
                    audioController:_audioController
                    error:&error];
    AudioUnitSetParameter(_highpass.audioUnit,
                          kHipassParam_CutoffFrequency,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    if ( !_highpass ) {
        // Report error
    }
    [self.audioController addFilter:self.highpass];
    
}

- (void)addPitchShift:(float)value {
    
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

- (void)addDelay:(float)value {

    AudioComponentDescription component = AEAudioComponentDescriptionMake(kAudioUnitManufacturer_Apple,
                                                                          kAudioUnitType_Effect,
                                                                          kAudioUnitSubType_Delay);
    NSError *error = NULL;
    self.delay = [[AEAudioUnitFilter alloc]
                    initWithComponentDescription:component
                    audioController:_audioController
                    error:&error];
    AudioUnitSetParameter(_delay.audioUnit,
                          kDelayParam_DelayTime,
                          kAudioUnitScope_Global,
                          0,
                          0,
                          0);
    AudioUnitSetParameter(_delay.audioUnit,
                          kDelayParam_Feedback,
                          kAudioUnitScope_Global,
                          0,
                          50,
                          0);
    AudioUnitSetParameter(_delay.audioUnit,
                          kDelayParam_WetDryMix,
                          kAudioUnitScope_Global,
                          0,
                          50,
                          0);
    if ( !_delay ) {
        // Report error
    }
    [self.audioController addFilter:self.delay];

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

- (void)changeHighpassValue:(float)value {
    
    AudioUnitSetParameter(_highpass.audioUnit,
                          kHipassParam_CutoffFrequency,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    
}

- (void)changePitchValue:(float)value {
    
    AudioUnitSetParameter(_changePitch.audioUnit,
                          kNewTimePitchParam_Pitch,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    
}

- (void)changeDelayValue:(float)value {

    AudioUnitSetParameter(_delay.audioUnit,
                          kDelayParam_DelayTime,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);

}

@end
