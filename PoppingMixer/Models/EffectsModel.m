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
@property (nonatomic, strong) NSMutableArray *effects;
//@property (nonatomic, strong) AEAudioUnitFilter *reverb;
//@property (nonatomic, strong) AEAudioUnitFilter *lowpass;
//@property (nonatomic, strong) AEAudioUnitFilter *highpass;
//@property (nonatomic, strong) AEAudioUnitFilter *changePitch;
//@property (nonatomic, strong) AEAudioUnitFilter *delay;

// basis
@property (nonatomic, strong) AEAudioController *audioController;
@property (nonatomic, strong) NSMutableArray *channels;
//@property (nonatomic, strong) NSMutableArray *isChannelSelected;

@end

/**********************************/
/**********************************/
/**********************************
         Reverb      0
         Lowpass     1
         Highpass    2
         PitchShift  3
         Delay       4
***********************************/
/**********************************/
/**********************************/

@implementation EffectsModel

- (id)init {
    
    self = [super init];
    if (!self) {
        return nil;
    }
    
    _musicAdded = NO;
    _effects = [NSMutableArray array];
    
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
    AEAudioFilePlayer *instrumental = [AEAudioFilePlayer audioFilePlayerWithURL:instrumentalMusic
                                                audioController:_audioController
                                                          error:NULL];
    NSURL *acapellaMusic = [[NSBundle mainBundle] URLForResource:@"lies_and_misery_acapella" withExtension:@"aif"];
    AEAudioFilePlayer *acapella = [AEAudioFilePlayer audioFilePlayerWithURL:acapellaMusic
                                                  audioController:_audioController
                                                            error:NULL];
    
    instrumental.loop = YES;
    acapella.loop = YES;

    
    self.channels = [NSMutableArray arrayWithObjects:instrumental, acapella, nil];
    AEAudioUnitFilter *c1 = _channels[0];
    AEAudioUnitFilter *c2 = _channels[1];
//    [_audioController addChannels:@[_channels[0], _channels[1]]];
    [_audioController addChannels:@[c1, c2]];
    
}

- (void)turnChannel:(int)channelId onOrOff:(BOOL)isOn forEffect:(int)effectId {

    NSLog(@"%@", self.effects);
    
    AEAudioUnitFilter *effect = _effects[effectId];
    AEAudioUnitChannel *channel = _channels[channelId];
    
    if(isOn){
        
        [_audioController addFilter:effect toChannel:channel];
        
    }
    else{

        [_audioController removeFilter:effect fromChannel:channel];
    
    }

}

- (void)togglePlaying {

    if(!self.musicAdded){
    
        [self playMusic];
        self.musicAdded = YES;
    
    }
    else {
    
        for (AEAudioFilePlayer *channel in self.channels) {
            channel.channelIsPlaying = !channel.channelIsPlaying;
        }
    
    }

}

#pragma init fx

- (void)initEffects {

    [self addReverb:0];
    [self addLowpass:100000];
    [self addHighpass:10];
    [self addPitchShift:1];
    [self addDelay:0];

}

- (void)addReverb:(float)value {
    
    AudioComponentDescription component = AEAudioComponentDescriptionMake(kAudioUnitManufacturer_Apple,
                                                                          kAudioUnitType_Effect,
                                                                          kAudioUnitSubType_Reverb2);
    NSError *error = NULL;
    AEAudioUnitFilter *reverb = [[AEAudioUnitFilter alloc]
                                 initWithComponentDescription:component
                                 audioController:_audioController
                                 error:&error];
    AudioUnitSetParameter(reverb.audioUnit,
                          kReverb2Param_DryWetMix,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    if ( !reverb ) {
        // Report error
    }
    [self.effects addObject:reverb];
    
}

- (void)addLowpass:(float)value {
    
    AudioComponentDescription component = AEAudioComponentDescriptionMake(kAudioUnitManufacturer_Apple,
                                                                          kAudioUnitType_Effect,
                                                                          kAudioUnitSubType_LowPassFilter);
    NSError *error = NULL;
    AEAudioUnitFilter *lowpass = [[AEAudioUnitFilter alloc]
                   initWithComponentDescription:component
                   audioController:_audioController
                   error:&error];
    AudioUnitSetParameter(lowpass.audioUnit,
                          kLowPassParam_CutoffFrequency,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    if ( !lowpass ) {
        // Report error
    }
    [self.effects addObject:lowpass];
    
}

- (void)addHighpass:(float)value {
    
    AudioComponentDescription component = AEAudioComponentDescriptionMake(kAudioUnitManufacturer_Apple,
                                                                          kAudioUnitType_Effect,
                                                                          kAudioUnitSubType_HighPassFilter);
    NSError *error = NULL;
    AEAudioUnitFilter *highpass = [[AEAudioUnitFilter alloc]
                    initWithComponentDescription:component
                    audioController:_audioController
                    error:&error];
    AudioUnitSetParameter(highpass.audioUnit,
                          kHipassParam_CutoffFrequency,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    if ( !highpass ) {
        // Report error
    }
    [self.effects addObject:highpass];
    
}

- (void)addPitchShift:(float)value {
    
    AudioComponentDescription component = AEAudioComponentDescriptionMake(kAudioUnitManufacturer_Apple,
                                                                          kAudioUnitType_Effect,
                                                                          kAudioUnitSubType_NewTimePitch);
    NSError *error = NULL;
    AEAudioUnitFilter *changePitch = [[AEAudioUnitFilter alloc]
                      initWithComponentDescription:component
                      audioController:_audioController
                      error:&error];
    AudioUnitSetParameter(changePitch.audioUnit,
                          kNewTimePitchParam_Pitch,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    
    if ( !changePitch ) {
        // Report error
    }
    [self.effects addObject:changePitch];
    
}

- (void)addDelay:(float)value {

    AudioComponentDescription component = AEAudioComponentDescriptionMake(kAudioUnitManufacturer_Apple,
                                                                          kAudioUnitType_Effect,
                                                                          kAudioUnitSubType_Delay);
    NSError *error = NULL;
    AEAudioUnitFilter *delay = [[AEAudioUnitFilter alloc]
                    initWithComponentDescription:component
                    audioController:_audioController
                    error:&error];
    AudioUnitSetParameter(delay.audioUnit,
                          kDelayParam_DelayTime,
                          kAudioUnitScope_Global,
                          0,
                          1.5,
                          0);
    AudioUnitSetParameter(delay.audioUnit,
                          kDelayParam_Feedback,
                          kAudioUnitScope_Global,
                          0,
                          20,
                          0);
    AudioUnitSetParameter(delay.audioUnit,
                          kDelayParam_WetDryMix,
                          kAudioUnitScope_Global,
                          0,
                          0,
                          0);
    if ( !delay ) {
        // Report error
    }
    [self.effects addObject:delay];

}

#pragma change value

- (void)changeReverbValue:(float)value {

    AEAudioUnitFilter *reverb = [self.effects objectAtIndex:0];
    AudioUnitSetParameter(reverb.audioUnit,
                          kReverb2Param_DryWetMix,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);

}

- (void)changeLowpassValue:(float)value {
    
    AEAudioUnitFilter *lowpass = [self.effects objectAtIndex:1];
    AudioUnitSetParameter(lowpass.audioUnit,
                          kLowPassParam_CutoffFrequency,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    
}

- (void)changeHighpassValue:(float)value {
    
    AEAudioUnitFilter *highpass = [self.effects objectAtIndex:2];
    AudioUnitSetParameter(highpass.audioUnit,
                          kHipassParam_CutoffFrequency,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    
}

- (void)changePitchValue:(float)value {
    
    AEAudioUnitFilter *pitchShift = [self.effects objectAtIndex:3];
    AudioUnitSetParameter(pitchShift.audioUnit,
                          kNewTimePitchParam_Pitch,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    
}

- (void)changeDelayWet:(float)value {

    AEAudioUnitFilter *delay = [self.effects objectAtIndex:4];
    AudioUnitSetParameter(delay.audioUnit,
                          kDelayParam_WetDryMix,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);

}

- (void)changeDelayTime:(float)value {
    
    AEAudioUnitFilter *delay = [self.effects objectAtIndex:4];
    AudioUnitSetParameter(delay.audioUnit,
                          kDelayParam_DelayTime,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
    
}

- (void)changeDelayFeedback:(float)value {
    
    AEAudioUnitFilter *delay = [self.effects objectAtIndex:4];
    AudioUnitSetParameter(delay.audioUnit,
                          kDelayParam_Feedback,
                          kAudioUnitScope_Global,
                          0,
                          value,
                          0);
}


@end
