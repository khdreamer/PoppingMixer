//
//  AudioModel.h
//  ElectricPiano
//
//  Created by Kevin Huang on 13/4/4.
//  Copyright (c) 2013年 Kevin Huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreAudio/CoreAudioTypes.h>

@interface AudioModel : NSObject

- (void)playNote:(int)midiNoteNum withGain:(int)gain;
- (void)stopNote:(int)midiNoteNum withGain:(int)gain;

@end
