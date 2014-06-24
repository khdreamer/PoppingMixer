//
//  EffectsModel.h
//  PoppingMixer
//
//  Created by Kevin Huang on 2014/6/24.
//  Copyright (c) 2014年 NMLab Project. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface EffectsModel : NSObject

// initialize

- (void)addAudioController;
- (void)togglePlaying;
- (void)initEffects;

// change value

- (void)changeReverbValue:(float)value;
- (void)changeLowpassValue:(float)value;
- (void)changePitchWithPitch:(float)value;

@end
