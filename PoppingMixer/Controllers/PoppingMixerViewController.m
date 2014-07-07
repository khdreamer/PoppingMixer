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
#import "RippleView.h"

@interface PoppingMixerViewController ()

@property (nonatomic, strong) AudioModel *audioModel;
@property (nonatomic, strong) EffectsModel *effectsModel;

@property (nonatomic, strong) UILabel *sensorStateLabel1;
@property (nonatomic) int sensorState1;

-(void) addBeat;

@end

@implementation PoppingMixerViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.ble = [[BLE alloc] initWithID:1];
    [self.ble controlSetup];
    self.ble.delegate = self;
    
    [self.effectsModel addAudioController];
    [self.effectsModel initEffects];
    
    self.sensorState1 = 0;
    self.function = 0; //0: Filters
    self.lockState = 0; //0: locked
    
    //    self.RSSIValueLabel = [[UILabel alloc] initWithFrame:CGRectMake(80, 100, 150, 150)];
    //    self.RSSIValueLabel.text = @"RSSIValue null";
    //    self.RSSIValueLabel.font = [UIFont fontWithName:@"ProximaNovaSemibold" size:20];
    //    [self.view addSubview:self.RSSIValueLabel];
    
    self.sensorStateLabel1 = [[UILabel alloc] initWithFrame:CGRectMake(50, 0, 200, 150)];
    self.sensorStateLabel1.text = @"sensor unconnected";
    self.sensorStateLabel1.font = [UIFont fontWithName:@"ProximaNovaSemibold" size:30];
    self.sensorStateLabel1.textColor = [UIColor whiteColor];
    [self.view addSubview:self.sensorStateLabel1];
    
    
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
}

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    RippleView *rippleView = [[RippleView alloc] initWithFrame:CGRectMake(50, 50, 200, 200)];
    [self.view addSubview:rippleView];

    
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

- (void) addBeat {
    
    NSLog(@"add beat");
    [self.audioModel playNote:24 withGain:400];
//    UIView *circleView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 50, 50)];
//    CAShapeLayer *circle = [CAShapeLayer ]
    
}

- (IBAction)playBackground:(id)sender {
    
    [self.effectsModel togglePlaying];
    
}



- (IBAction)resetPanel:(UIButton *)sender {
    
    self.lockState = 0;
    [self.lockButton setImage:[UIImage imageNamed:@"lock32@ipad2x.png"] forState:UIControlStateNormal];
}

- (IBAction)resetSensor:(UIButton *)sender {
    NSLog(@"reset sensor..");
    
    UInt8 buf[1] = {0x15};
    NSData *data = [[NSData alloc] initWithBytes:buf length:1];
    [self.ble write:data];
}

- (IBAction)switchLockState:(id)sender {
    NSLog(@"switch LockState!");
    if( self.lockState == 1 ) {
        self.lockState = 0;
//        [self.lockButton setTitle:@"Locked" forState:UIControlStateNormal];
        [self.lockButton setImage:[UIImage imageNamed:@"lock32@ipad2x.png"] forState:UIControlStateNormal];
    }
    else {
        self.lockState = 1;
//        [self.lockButton setTitle:@"Unlocked" forState:UIControlStateNormal];
        [self.lockButton setImage:[UIImage imageNamed:@"unlock32@ipad2x.png"] forState:UIControlStateNormal];
    }
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
    
    [self.ble findBLEPeripherals:2];
    
    [NSTimer scheduledTimerWithTimeInterval:2.0f target:self selector:@selector(connectToBLETimer:) userInfo:nil repeats:NO];
}

- (void) connectToBLETimer:(NSTimer*) timer
{
    if(self.ble.peripherals.count > 0){
        NSLog(@"BLE peripheral found. Connecting...");
        [self.ble connectPeripheral:[self.ble.peripherals objectAtIndex:0]];
    }
}

#pragma mark - BLE Delegate

-(void) bleDidConnectForID:(int)ID
{
    NSLog(@"Connect to BLE device #%d successfully. YO!", ID);
    UInt8 buf[1] = {0x49};
    NSData *data = [[NSData alloc] initWithBytes:buf length:1];
    
    self.sensorStateLabel1.text = @"CHIPMUNK";
    [self.ble write:data];
}

-(void) bleDidDisconnectForID:(int)ID
{
    NSLog(@"Disconnect from BLE device #%d successfully. BOO...", ID);
    
    self.sensorState1 = 0;
    self.sensorStateLabel1.text = @"Disconnected";
    
}

-(void) bleDidUpdateRSSI:(NSNumber *) rssi ForID:(int)ID
{
    
    //    self.RSSIValueLabel.text = rssi.stringValue;
}

-(void) bleDidReceiveData:(unsigned char *)data length:(int)length ForID:(int)ID
{
    //    NSLog(@"Length: %d", length);
    
    UInt8 Op;
    UInt8 Data;
    
//    Op = data[length-2];
    Data = data[length-1];
    
    NSLog(@"Op=%d, Data=%d", Op,Data);
    
    if( self.lockState == 1 ){ //unlocked
        switch (Data) {
            case 0:{
                [self addBeat];
                break;
            }
            case 1:{
                
                break;
            }
            case 2:{
                break;
            }
            case 3:{
                break;
            }
            default:
                break;
        }
    }
    //    self.packetSizeLabel.text = [NSString stringWithFormat:@"%d",length];
}

@end
