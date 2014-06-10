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

@property (nonatomic, strong) UILabel *RSSIValueLabel;
@property (nonatomic, strong) UILabel *sensorStateLabel;
@property (nonatomic, strong) UILabel *packetSizeLabel;

@property (nonatomic) int sensorState;

@end

@implementation PoppingMixerViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.ble = [[BLE alloc] init];
    [self.ble controlSetup];
    self.ble.delegate = self;
    
    NSLog(@"ble.CM.state = %d", self.ble.CM.state);
//    [self scanPeripheral];
    
    [self addAudioController];
    [self playBackgroundMusic];
    [self addReverb];
    
    self.sensorState = 0;
    
    self.RSSIValueLabel = [[UILabel alloc] initWithFrame:CGRectMake(50, 100, 150, 150)];
    self.RSSIValueLabel.text = @"RSSIValue null";
    self.RSSIValueLabel.font = [UIFont fontWithName:@"ProximaNovaSemibold" size:20];
    [self.view addSubview:self.RSSIValueLabel];

    self.sensorStateLabel = [[UILabel alloc] initWithFrame:CGRectMake(300, 100, 150, 150)];
    self.sensorStateLabel.text = @"sensorState null";
    self.sensorStateLabel.font = [UIFont fontWithName:@"ProximaNovaSemibold" size:20];
    [self.view addSubview:self.sensorStateLabel];
    
    self.packetSizeLabel = [[UILabel alloc] initWithFrame:CGRectMake(550, 100, 150, 150)];
    self.packetSizeLabel.text = @"packetSize null";
    self.packetSizeLabel.font = [UIFont fontWithName:@"ProximaNovaSemibold" size:20];
    [self.view addSubview:self.packetSizeLabel];
    
    NSLog(@"slider max: %f, min: %f", self.reverbSlider.maximumValue, self.reverbSlider.minimumValue);

}

- (void) viewWillDisappear:(BOOL)animated
{
    NSLog(@"ViewController will disappear");
    if (self.ble.activePeripheral)
        if(self.ble.activePeripheral.isConnected)
        {
            //send BLE shield "0" to turn off transmission
            UInt8 buf[1] = {0x30};
            
            NSData *data = [[NSData alloc] initWithBytes:buf length:1];
            [self.ble write:data];
            // after that cancel connection
            [[self.ble CM] cancelPeripheralConnection:[self.ble activePeripheral]];
        }
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
    [self.audioModel playNote:24 withGain:400];
    
}

- (IBAction)applyReverb:(UISlider *)sender {
    
    AudioUnitSetParameter(_reverb.audioUnit,
                          kReverb2Param_DryWetMix,
                          kAudioUnitScope_Global,
                          0,
                          sender.value,
                          0);
    
}

#pragma mark - BLE

- (IBAction) connect: (id) sender
{
    NSLog(@"Start scanning for BLE peripherals ...");
    NSLog(@"ble.CM.state = %d", self.ble.CM.state);
    [self scanPeripheral];
}

- (void) scanPeripheral
{
    if (self.ble.activePeripheral)
        if(self.ble.activePeripheral.isConnected)
        {
            [[self.ble CM] cancelPeripheralConnection:[self.ble activePeripheral]];
            return;
        }
    
    if (self.ble.peripherals)
        self.ble.peripherals = nil;
    
    [self.ble findBLEPeripherals:2];
    
    [NSTimer scheduledTimerWithTimeInterval:2.0f target:self selector:@selector(connectToBLETimer:) userInfo:nil repeats:NO];
}

- (void) connectToBLETimer:(NSTimer*) timer
{
    if(self.ble.peripherals.count > 0){
        NSLog(@"BLE peripheral found.");
        [self.ble connectPeripheral:[self.ble.peripherals objectAtIndex:0]];
    }
}

#pragma mark - BLE Delegate
-(void) bleDidConnect
{
    NSLog(@"Connect to BLE device successfully. YO!");
    UInt8 buf[1] = {0x49};
    
    self.sensorStateLabel.text = @"initial: IDLE";
    
    NSData *data = [[NSData alloc] initWithBytes:buf length:1];
    [self.ble write:data];
}

-(void) bleDidDisconnect
{
    NSLog(@"Disconnect from BLE device successfully. BOO...");
}

-(void) bleDidUpdateRSSI:(NSNumber *) rssi
{
    
    self.RSSIValueLabel.text = rssi.stringValue;
}

-(void) bleDidReceiveData:(unsigned char *)data length:(int)length
{
    NSLog(@"Length: %d", length);
    
    UInt8 Op;
    UInt8 Data;
    
    Op = data[length-2];
    Data = data[length-1];
    
    NSLog(@"Op = %d, Data = %d", Op,Data);
    
    switch (Op) {
        case 0:{
            if(Data == 1) {
                self.sensorStateLabel.text = @"REVERB";
                self.sensorState = 1;
            }
            else if(Data == 0) {
                self.sensorStateLabel.text = @"IDLE";
                self.sensorState = 0;
            }
            break;
        }
        case 1:{
            if(Data == 10){
                NSLog(@"slider +10!");
                float nextSliderValue = self.reverbSlider.value+10;
                float maxSliderValue = self.reverbSlider.maximumValue;
                if(nextSliderValue <= maxSliderValue){
                    [self.reverbSlider setValue:nextSliderValue animated:YES];
                    AudioUnitSetParameter(_reverb.audioUnit,
                                          kReverb2Param_DryWetMix,
                                          kAudioUnitScope_Global,
                                          0,
                                          nextSliderValue,
                                          0);
                }
                else {
                    [self.reverbSlider setValue:maxSliderValue animated:YES];
                    AudioUnitSetParameter(_reverb.audioUnit,
                                          kReverb2Param_DryWetMix,
                                          kAudioUnitScope_Global,
                                          0,
                                          maxSliderValue,
                                          0);
                }
            }
            else if(Data == 20){
                NSLog(@"slider -10!");
                float nextSliderValue = self.reverbSlider.value-10;
                float minSliderValue = self.reverbSlider.minimumValue;
                if(nextSliderValue >= minSliderValue){
                    [self.reverbSlider setValue:nextSliderValue animated:YES];
                    AudioUnitSetParameter(_reverb.audioUnit,
                                          kReverb2Param_DryWetMix,
                                          kAudioUnitScope_Global,
                                          0,
                                          nextSliderValue,
                                          0);
                }
                else {
                    [self.reverbSlider setValue:minSliderValue animated:YES];
                    AudioUnitSetParameter(_reverb.audioUnit,
                                          kReverb2Param_DryWetMix,
                                          kAudioUnitScope_Global,
                                          0,
                                          minSliderValue,
                                          0);
                }
            }
            break;
        }
        default:
            break;
    }
    
    switch(self.sensorState){
        case 0:{
            self.sensorStateLabel.text = [NSString stringWithFormat:@"IDLE"];
            break;
        }
        case 1:{
            self.sensorStateLabel.text = [NSString stringWithFormat:@"REVERB"];
            break;
        }
        default:
            break;
    }
    
    self.packetSizeLabel.text = [NSString stringWithFormat:@"%d",length];
}


@end
