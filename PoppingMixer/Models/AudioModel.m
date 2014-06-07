//
//  AudioModel.m
//  ElectricPiano
//
//  Created by Kevin Huang on 13/4/4.
//  Copyright (c) 2013年 Kevin Huang. All rights reserved.
//

#import "AudioModel.h"
#import <AssertMacros.h>

// some MIDI constants:
enum {
	kMIDIMessage_NoteOn    = 0x9,
	kMIDIMessage_NoteOff   = 0x8,
};

@interface AudioModel ()

@property (readwrite) Float64   graphSampleRate;
@property (readwrite) AUGraph   processingGraph;
@property (readwrite) AudioUnit samplerUnit;
@property (readwrite) AudioUnit ioUnit;

- (BOOL) createAUGraph;
- (void) configureAndStartAudioProcessingGraph: (AUGraph) graph;
-(OSStatus) loadFromDLSOrSoundFont: (NSURL *)bankURL withPatch: (int)presetNumber;

@end

@implementation AudioModel

- (id)init {

    self = [super init];
    if (!self) {
        return nil;
    }
    
    self.graphSampleRate = 44100.0;  
    [self createAUGraph];
    [self configureAndStartAudioProcessingGraph: self.processingGraph];
    [self loadPreset];
    NSLog(@"init");
    
    return self;
    
}

#pragma mark Audio setup

// Create an audio processing graph.
- (BOOL)createAUGraph {
    
	OSStatus result = noErr;
	AUNode samplerNode, ioNode;
    
    // Specify the common portion of an audio unit's identify, used for both audio units
    // in the graph.
	AudioComponentDescription cd = {};
	cd.componentManufacturer     = kAudioUnitManufacturer_Apple;
	cd.componentFlags            = 0;
	cd.componentFlagsMask        = 0;
    
    // Instantiate an audio processing graph
	result = NewAUGraph (&_processingGraph);
    NSCAssert (result == noErr, @"Unable to create an AUGraph object. Error code: %d '%.4s'", (int) result, (const char *)&result);
    
	//Specify the Sampler unit, to be used as the first node of the graph
	cd.componentType = kAudioUnitType_MusicDevice;
	cd.componentSubType = kAudioUnitSubType_Sampler;
	
    // Add the Sampler unit node to the graph
	result = AUGraphAddNode (self.processingGraph, &cd, &samplerNode);
    NSCAssert (result == noErr, @"Unable to add the Sampler unit to the audio processing graph. Error code: %d '%.4s'", (int) result, (const char *)&result);
    
	// Specify the Output unit, to be used as the second and final node of the graph
	cd.componentType = kAudioUnitType_Output;
	cd.componentSubType = kAudioUnitSubType_RemoteIO;
    
    // Add the Output unit node to the graph
	result = AUGraphAddNode (self.processingGraph, &cd, &ioNode);
    NSCAssert (result == noErr, @"Unable to add the Output unit to the audio processing graph. Error code: %d '%.4s'", (int) result, (const char *)&result);
    
    // Open the graph
	result = AUGraphOpen (self.processingGraph);
    NSCAssert (result == noErr, @"Unable to open the audio processing graph. Error code: %d '%.4s'", (int) result, (const char *)&result);
    
    // Connect the Sampler unit to the output unit
	result = AUGraphConnectNodeInput (self.processingGraph, samplerNode, 0, ioNode, 0);
    NSCAssert (result == noErr, @"Unable to interconnect the nodes in the audio processing graph. Error code: %d '%.4s'", (int) result, (const char *)&result);
    
	// Obtain a reference to the Sampler unit from its node
	result = AUGraphNodeInfo (self.processingGraph, samplerNode, 0, &_samplerUnit);
    NSCAssert (result == noErr, @"Unable to obtain a reference to the Sampler unit. Error code: %d '%.4s'", (int) result, (const char *)&result);
    
	// Obtain a reference to the I/O unit from its node
	result = AUGraphNodeInfo (self.processingGraph, ioNode, 0, &_ioUnit);
    NSCAssert (result == noErr, @"Unable to obtain a reference to the I/O unit. Error code: %d '%.4s'", (int) result, (const char *)&result);
    
    return YES;
}


// Starting with instantiated audio processing graph, configure its
// audio units, initialize it, and start it.
- (void)configureAndStartAudioProcessingGraph: (AUGraph) graph {
    
    OSStatus result = noErr;
    UInt32 framesPerSlice = 0;
    UInt32 framesPerSlicePropertySize = sizeof (framesPerSlice);
    UInt32 sampleRatePropertySize = sizeof (self.graphSampleRate);
    
    result = AudioUnitInitialize (self.ioUnit);
    NSCAssert (result == noErr, @"Unable to initialize the I/O unit. Error code: %d '%.4s'", (int) result, (const char *)&result);
    
    // Set the I/O unit's output sample rate.
    result =    AudioUnitSetProperty (self.ioUnit, kAudioUnitProperty_SampleRate,
                                      kAudioUnitScope_Output, 0,
                                      &_graphSampleRate, sampleRatePropertySize);
    
    NSAssert (result == noErr, @"AudioUnitSetProperty (set Sampler unit output stream sample rate). Error code: %d '%.4s'", (int) result, (const char *)&result);
    
    // Obtain the value of the maximum-frames-per-slice from the I/O unit.
    result =    AudioUnitGetProperty (self.ioUnit, kAudioUnitProperty_MaximumFramesPerSlice,
                                      kAudioUnitScope_Global, 0,
                                      &framesPerSlice, &framesPerSlicePropertySize);
    
    NSCAssert (result == noErr, @"Unable to retrieve the maximum frames per slice property from the I/O unit. Error code: %d '%.4s'", (int) result, (const char *)&result);
    
    // Set the Sampler unit's output sample rate.
    result =    AudioUnitSetProperty (self.samplerUnit, kAudioUnitProperty_SampleRate,
                                      kAudioUnitScope_Output, 0,
                                      &_graphSampleRate, sampleRatePropertySize);
    
    NSAssert (result == noErr, @"AudioUnitSetProperty (set Sampler unit output stream sample rate). Error code: %d '%.4s'", (int) result, (const char *)&result);
    
    // Set the Sampler unit's maximum frames-per-slice.
    result =    AudioUnitSetProperty (self.samplerUnit, kAudioUnitProperty_MaximumFramesPerSlice,
                                      kAudioUnitScope_Global, 0,
                                      &framesPerSlice, framesPerSlicePropertySize);
    
    NSAssert( result == noErr, @"AudioUnitSetProperty (set Sampler unit maximum frames per slice). Error code: %d '%.4s'", (int) result, (const char *)&result);
    
    
    if (graph) {
        
        // Initialize the audio processing graph.
        result = AUGraphInitialize (graph);
        NSAssert (result == noErr, @"Unable to initialze AUGraph object. Error code: %d '%.4s'", (int) result, (const char *)&result);
        
        // Start the graph
        result = AUGraphStart (graph);
        NSAssert (result == noErr, @"Unable to start audio processing graph. Error code: %d '%.4s'", (int) result, (const char *)&result);
        
        // Print out the graph to the console
        CAShow (graph); 
    }
}

// Load the Drum preset
- (void)loadPreset {
    
	NSURL *presetURL = [[NSURL alloc] initFileURLWithPath:[[NSBundle mainBundle] pathForResource:@"HS R8 Drums" ofType:@"sf2"]];

	if (presetURL)
        NSLog(@"Attempting to load preset '%@'\n", [presetURL description]);
	else
		NSLog(@"COULD NOT GET PRESET PATH!");
    
    [self loadFromDLSOrSoundFont: presetURL withPatch: 1];
}

- (OSStatus)loadFromDLSOrSoundFont: (NSURL *)bankURL withPatch: (int)presetNumber {
    
    OSStatus result = noErr;
    
    // fill out a bank preset data structure
    AUSamplerBankPresetData bpdata;
    bpdata.bankURL  = (__bridge CFURLRef) bankURL;
    bpdata.bankMSB  = kAUSampler_DefaultMelodicBankMSB;
    bpdata.bankLSB  = kAUSampler_DefaultBankLSB;
    bpdata.presetID = (UInt8) presetNumber;
    
    // set the kAUSamplerProperty_LoadPresetFromBank property
    result = AudioUnitSetProperty(self.samplerUnit, kAUSamplerProperty_LoadPresetFromBank,
                                  kAudioUnitScope_Global, 0,
                                  &bpdata, sizeof(bpdata));
    
    // check for errors
    NSCAssert (result == noErr,
               @"Unable to set the preset property on the Sampler. Error code:%d '%.4s'",
               (int) result,
               (const char *)&result);
    
    return result;
    
}

#pragma mark -
#pragma mark Audio control

//[self stopNote:midiNoteNum withGain:_notes[midiNoteNum-MIDI_START]];


- (void)playNote:(int)midiNoteNum withGain:(int)gain{
    
	//UInt32 noteNum = 65;
	//UInt32 onVelocity = 127;
	UInt32 noteCommand = kMIDIMessage_NoteOn << 4 | 0;
    
    OSStatus result = noErr;
	require_noerr (result = MusicDeviceMIDIEvent (self.samplerUnit, noteCommand, midiNoteNum, gain, 0), logTheError);
    
logTheError:
    if (result != noErr) NSLog (@"Unable to start playing the low note. Error code: %d '%.4s'\n", (int) result, (const char *)&result);
    
}

- (void)stopNote:(int)midiNoteNum withGain:(int)gain{
    
	//UInt32 noteNum = 65;
	UInt32 noteCommand = kMIDIMessage_NoteOff << 4 | 0;
	
    OSStatus result = noErr;
	require_noerr (result = MusicDeviceMIDIEvent (self.samplerUnit, noteCommand, midiNoteNum, 0, 0), logTheError);
    
logTheError:
    if (result != noErr) NSLog (@"Unable to stop playing the low note. Error code: %d '%.4s'\n", (int) result, (const char *)&result);
}




@end
