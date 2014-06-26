//
//  EffectsModel.h
//  PoppingMixer
//
//  Created by Kevin Huang on 2014/6/24.
//  Copyright (c) 2014年 NMLab Project. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface EffectsModel : NSObject

// initialize and bsic methods

- (void)addAudioController;
- (void)togglePlaying;
- (void)initEffects;
- (void)turnChannel:(int)channelId onOrOff:(BOOL)isOn forEffect:(int)effectId;

// change value

- (void)changeReverbValue:(float)value;
- (void)changeLowpassValue:(float)value;
- (void)changePitchValue:(float)value;
- (void)changeHighpassValue:(float)value;
- (void)changeDelayWet:(float)value;
- (void)changeDelayFeedback:(float)value;
- (void)changeDelayTime:(float)value;

@end
