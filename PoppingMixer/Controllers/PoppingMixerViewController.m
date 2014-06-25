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
#import "EffectsModel.h"

@interface PoppingMixerViewController ()

@property (nonatomic, strong) AudioModel *audioModel;
@property (nonatomic, strong) EffectsModel *effectsModel;

//@property (nonatomic, strong) UILabel *RSSIValueLabel;
@property (nonatomic, strong) UILabel *sensorStateLabel1;
@property (nonatomic, strong) UILabel *sensorStateLabel2;
//@property (nonatomic, strong) UILabel *packetSizeLabel;

@property (nonatomic) int sensorState1;
@property (nonatomic) int sensorState2;

@end

@implementation PoppingMixerViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.ble = [[BLE alloc] initWithID:1];
    [self.ble controlSetup];
    self.ble.delegate = self;
    
    self.ble2 = [[BLE alloc] initWithID:2];
    [self.ble2 controlSetup];
    self.ble2.delegate = self;
    
//    NSLog(@"ble.CM.state = %d", self.ble.CM.state);
//    [self scanPeripheral];
    
    [self.effectsModel addAudioController];
    [self.effectsModel initEffects];
    
    self.sensorState1 = 0;
    self.sensorState2 = 0;
    
//    self.RSSIValueLabel = [[UILabel alloc] initWithFrame:CGRectMake(80, 100, 150, 150)];
//    self.RSSIValueLabel.text = @"RSSIValue null";
//    self.RSSIValueLabel.font = [UIFont fontWithName:@"ProximaNovaSemibold" size:20];
//    [self.view addSubview:self.RSSIValueLabel];

    self.sensorStateLabel1 = [[UILabel alloc] initWithFrame:CGRectMake(50, 0, 150, 150)];
    self.sensorStateLabel1.text = @"sensorState null";
    self.sensorStateLabel1.font = [UIFont fontWithName:@"ProximaNovaSemibold" size:30];
    [self.view addSubview:self.sensorStateLabel1];
    
    self.sensorStateLabel2 = [[UILabel alloc] initWithFrame:CGRectMake(550, 0, 150, 150)];
    self.sensorStateLabel2.text = @"sensorState null";
    self.sensorStateLabel2.font = [UIFont fontWithName:@"ProximaNovaSemibold" size:30];
    [self.view addSubview:self.sensorStateLabel2];
    
//    self.packetSizeLabel = [[UILabel alloc] initWithFrame:CGRectMake(580, 100, 150, 150)];
//    self.packetSizeLabel.text = @"packetSize null";
//    self.packetSizeLabel.font = [UIFont fontWithName:@"ProximaNovaSemibold" size:20];
//    [self.view addSubview:self.packetSizeLabel];
    
    NSLog(@"slider max: %f, min: %f", self.reverbSlider.maximumValue, self.reverbSlider.minimumValue);

}

- (void) viewWillDisappear:(BOOL)animated
{
    NSLog(@"ViewController will disappear");
    if (self.ble.activePeripheral){
//        if(self.ble.activePeripheral.isConnected)
        if(self.ble.activePeripheral.state == CBPeripheralStateConnected)
        {
            //send BLE shield "0" to turn off transmission
            UInt8 buf[1] = {0x30};
            
            NSData *data = [[NSData alloc] initWithBytes:buf length:1];
            [self.ble write:data];
            // after that cancel connection
            [[self.ble CM] cancelPeripheralConnection:[self.ble activePeripheral]];
        }
    }
    
    if (self.ble2.activePeripheral){
        if(self.ble2.activePeripheral.state == CBPeripheralStateConnected)
        {
            //send BLE shield "0" to turn off transmission
            UInt8 buf[1] = {0x30};
            
            NSData *data = [[NSData alloc] initWithBytes:buf length:1];
            [self.ble2 write:data];
            // after that cancel connection
            [[self.ble2 CM] cancelPeripheralConnection:[self.ble2 activePeripheral]];
        }
    }
}

#pragma mark - Getters

- (AudioModel *)audioModel {
    
    if(!_audioModel){
        
        _audioModel = [[AudioModel alloc] init];
        
    }
    return _audioModel;
    
}

- (EffectsModel *)effectsModel {
    
    if(!_effectsModel){
        
        _effectsModel = [[EffectsModel alloc] init];
        
    }
    return _effectsModel;
    
}

#pragma mark - Stuff

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Effects

- (IBAction)addBeat:(id)sender {
    
    NSLog(@"add beat");
    [self.audioModel playNote:24 withGain:400];
    
}

- (IBAction)playBackground:(id)sender {
    
    [self.effectsModel togglePlaying];
    
}

- (IBAction)applyReverb:(UISlider *)sender {
    
    [self.effectsModel changeReverbValue:sender.value];
    
}

- (IBAction)addLowpass:(UISlider *)sender {
    
    [self.effectsModel changeLowpassValue:powf(10.0, sender.value)];
    
}

- (IBAction)changePitch:(UISlider *)sender {
    
    [self.effectsModel changePitchValue:sender.value];
    
}

- (IBAction)changeDelay:(UISlider *)sender {
    
    [self.effectsModel changeDelayValue:sender.value];
    
}

- (IBAction)addHighPass:(UISlider *)sender {
    
    [self.effectsModel changeHighpassValue:powf(10.0, sender.value)];

}

#pragma mark - BLE

- (IBAction) connect: (id) sender
{
    NSLog(@"Start scanning for BLE peripherals ...");
//    NSLog(@"ble.CM.state = %d", self.ble.CM.state);
    [self scanPeripheral];
}

- (void) scanPeripheral
{
    if (self.ble.activePeripheral){
        if(self.ble.activePeripheral.state == CBPeripheralStateConnected)
        {
            [[self.ble CM] cancelPeripheralConnection:[self.ble activePeripheral]];
            return;
        }
    }
    
    if (self.ble.peripherals){
        self.ble.peripherals = nil;
    }
    
    if (self.ble2.activePeripheral){
        if(self.ble2.activePeripheral.state == CBPeripheralStateConnected)
        {
            [[self.ble2 CM] cancelPeripheralConnection:[self.ble2 activePeripheral]];
            return;
        }
    }
    
    if (self.ble2.peripherals){
        self.ble2.peripherals = nil;
    }
    
    [self.ble findBLEPeripherals:5];
    [self.ble2 findBLEPeripherals:5];
    
    [NSTimer scheduledTimerWithTimeInterval:5.0f target:self selector:@selector(connectToBLETimer:) userInfo:nil repeats:NO];
}

- (void) connectToBLETimer:(NSTimer*) timer
{
    if(self.ble.peripherals.count > 0){
        NSLog(@"BLE peripheral found. Connecting...");
        [self.ble connectPeripheral:[self.ble.peripherals objectAtIndex:0]];

        if(self.ble.peripherals.count == 2) {
            CBPeripheral *p1 = [self.ble.peripherals objectAtIndex:0];
            CBPeripheral *p2 = [self.ble.peripherals objectAtIndex:1];
            NSLog(@"ble: identifier 1: %@, identifier 2: %@", [p1.identifier UUIDString], [p2.identifier UUIDString]);
            
            if(self.ble2.peripherals.count == 2){
                CBPeripheral *p3 = [self.ble2.peripherals objectAtIndex:0];
                CBPeripheral *p4 = [self.ble2.peripherals objectAtIndex:1];
                NSLog(@"ble2: identifier 1: %@, identifier 2: %@", [p3.identifier UUIDString], [p4.identifier UUIDString]);
            }
            
            NSLog(@"Second BLE peripherals found. Connecting...");
//            CBPeripheral *p = [self.ble2.peripherals objectAtIndex:0];
            [self.ble2 connectPeripheral:[self.ble.peripherals objectAtIndex:1]];
        }
    }
}

#pragma mark - BLE Delegate

-(void) bleDidConnectForID:(int)ID
{
    NSLog(@"Connect to BLE device #%d successfully. YO!", ID);
    UInt8 buf[1] = {0x49};
    NSData *data = [[NSData alloc] initWithBytes:buf length:1];
    
    if(ID == 1) {
        self.sensorStateLabel1.text = @"initial: IDLE";
        [self.ble write:data];
    }
    else if(ID == 2) {
        self.sensorStateLabel2.text = @"initial: IDLE";
        [self.ble2 write:data];
    }
}

-(void) bleDidDisconnectForID:(int)ID
{
    NSLog(@"Disconnect from BLE device #%d successfully. BOO...", ID);
    if(ID == 1){
        self.sensorState1 = 0;
        self.sensorStateLabel1.text = @"Disconnected";
    }
    else if(ID == 2){
        self.sensorState2 = 0;
        self.sensorStateLabel2.text = @"Disconnected";
    }
    
}

-(void) bleDidUpdateRSSI:(NSNumber *) rssi ForID:(int)ID
{
    
//    self.RSSIValueLabel.text = rssi.stringValue;
}

-(void) bleDidReceiveData:(unsigned char *)data length:(int)length ForID:(int)ID
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
                if(ID == 1) {
                    self.sensorStateLabel1.text = @"REVERB";
                    self.sensorState1 = 1;
                }
                else if(ID == 2){
                    self.sensorStateLabel2.text = @"REVERB";
                    self.sensorState2 = 1;
                }
            }
            else if(Data == 0) {
                if(ID == 1){
                    self.sensorStateLabel1.text = @"IDLE";
                    self.sensorState1 = 0;
                }
                else if(ID == 2){
                    self.sensorStateLabel2.text = @"IDLE";
                    self.sensorState2 = 0;
                }
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
                    [self.effectsModel changeReverbValue:nextSliderValue];

                }
                else {
                    [self.reverbSlider setValue:maxSliderValue animated:YES];
                    [self.effectsModel changeReverbValue:maxSliderValue];

                }
            }
            else if(Data == 20){
                NSLog(@"slider -10!");
                float nextSliderValue = self.reverbSlider.value-10;
                float minSliderValue = self.reverbSlider.minimumValue;
                if(nextSliderValue >= minSliderValue){
                    [self.reverbSlider setValue:nextSliderValue animated:YES];
                    [self.effectsModel changeReverbValue:nextSliderValue];

                }
                else {
                    [self.reverbSlider setValue:minSliderValue animated:YES];
                    [self.effectsModel changeReverbValue:minSliderValue];

                }
            }
            break;
        }
        default:
            break;
    }
    
    switch(self.sensorState1){
        case 0:{
            self.sensorStateLabel1.text = [NSString stringWithFormat:@"IDLE"];
            break;
        }
        case 1:{
            self.sensorStateLabel1.text = [NSString stringWithFormat:@"REVERB"];
            break;
        }
        default:
            break;
    }

    switch(self.sensorState2){
        case 0:{
            self.sensorStateLabel2.text = [NSString stringWithFormat:@"IDLE"];
            break;
        }
        case 1:{
            self.sensorStateLabel2.text = [NSString stringWithFormat:@"REVERB"];
            break;
        }
        default:
            break;
    }

//    self.packetSizeLabel.text = [NSString stringWithFormat:@"%d",length];
}


@end
