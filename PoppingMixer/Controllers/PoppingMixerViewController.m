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

@property (nonatomic, strong) UILabel *sensorStateLabel1;
@property (nonatomic) int sensorState1;

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

- (IBAction)toggleChannel:(UISwitch *)sender {
    
    // 0 ===> instrumental
    // 1 ===> acapella
    int channelId = sender.tag % 2;
    int effectId = (int)(sender.tag / 2);
    NSLog(@"%d", sender.tag);
    [self.effectsModel turnChannel:channelId onOrOff:sender.on forEffect:effectId];
    
}

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

- (IBAction)changeDelayWet:(UISlider *)sender {
    
    [self.effectsModel changeDelayWet:sender.value];
    
}

- (IBAction)changeDelayTime:(UISlider *)sender {
    
    int value = floor(sender.value);
    [self.effectsModel changeDelayTime:value*0.5];
    self.delayTimeSlider.value = value;
    
}

- (IBAction)changeDelayFeedback:(UISlider *)sender {
    
    [self.effectsModel changeDelayFeedback:sender.value];
    
}

- (IBAction)resetPanel:(UIButton *)sender {
    [self.reverbSlider setValue:0 animated:YES];
    [self.effectsModel changeReverbValue:0];
    
    [self.lowpassSlider setValue:4.4 animated:YES];
    [self.effectsModel changeLowpassValue:4.4];
    
    [self.highpassSlider setValue:1 animated:YES];
    [self.effectsModel changeHighpassValue:1];
    
    [self.pitchShiftSlider setValue:0 animated:YES];
    [self.effectsModel changePitchValue:0];
    
    [self.delayTimeSlider setValue:0 animated:YES];
    [self.effectsModel changeDelayTime:0];
    
    [self.delayFeedbackSlider setValue:0 animated:YES];
    [self.effectsModel changeDelayFeedback:0];
    
    [self.delayWetSlider setValue:0 animated:YES];
    [self.effectsModel changeDelayWet:0];
    
    /////
    
    [self.reverbInstrumentalSwitch setOn:NO animated:YES];
    [self.reverbVocalSwitch setOn:NO animated:YES];
    
    [self.lowpassInstrumentalSwitch setOn:NO animated:YES];
    [self.lowpassVocalSwitch setOn:NO animated:YES];
    
    [self.highpassInstrumentalSwitch setOn:NO animated:YES];
    [self.highpassVocalSwitch setOn:NO animated:YES];
    
    [self.chipmunkInstrumentalSwitch setOn:NO animated:YES];
    [self.chipmunkVocalSwitch setOn:NO animated:YES];
    
    [self.delaytimeInstrumentalSwitch setOn:NO animated:YES];
    [self.delaytimeVocalSwitch setOn:NO animated:YES];
    
    /////
    
    
    for( int i=0 ; i<5 ; i++){
        [self.effectsModel turnChannel:0 onOrOff:NO forEffect:i];
        [self.effectsModel turnChannel:1 onOrOff:NO forEffect:i];
    }

    
    self.lockState = 0;
//    [self.lockButton setTitle:@"Locked" forState:UIControlStateNormal];
    [self.lockButton setImage:[UIImage imageNamed:@"lock32@ipad2x.png"] forState:UIControlStateNormal];

    self.function = 0;
    [self.switchFunctionButton setTitle:@"Filters" forState:UIControlStateNormal];
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

- (IBAction)switchFunction:(id)sender {
    NSLog(@"switch Function!");
    if( self.function == 1 ) {
        self.function = 0;
        [self.switchFunctionButton setTitle:@"Filters" forState:UIControlStateNormal];
    }
    else {
        self.function = 1;
        [self.switchFunctionButton setTitle:@"Delays" forState:UIControlStateNormal];
    }
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
    
    Op = data[length-2];
    Data = data[length-1];
    
    NSLog(@"Op=%d, Data=%d", Op,Data);
    
    if( self.lockState == 1 ){ //unlocked
        switch (Op) {
            case 0:{
                if( self.function == 0 ){
                    if(Data == 0) {
                        
                        self.sensorStateLabel1.text = @"Chipmunk";
                        self.sensorState1 = 1;
                        
                    }
                    else if(Data == 1) {
                        
                        self.sensorStateLabel1.text = @"Lowpass";
                        self.sensorState1 = 0;
                        
                    }
                    else if(Data == 2) {
                        self.sensorStateLabel1.text = @"Highpass";
                        self.sensorState1 = 0;
                        
                    }
                }
                else if( self.function == 1 ){
                    if(Data == 0) {
                        
                        self.sensorStateLabel1.text = @"Delay Feedback";
                        self.sensorState1 = 1;
                        
                    }
                    else if(Data == 1) {
                        
                        self.sensorStateLabel1.text = @"Delay Time";
                        self.sensorState1 = 0;
                        
                    }
                    else if(Data == 2) {
                        self.sensorStateLabel1.text = @"Delay Dry/Wet";
                        self.sensorState1 = 0;
                        
                    }
                }
                break;
            }
            case 1:{
                if( self.function == 0 ){
                    if(Data == 10){
                        float nextSliderValue = self.pitchShiftSlider.value+20;
                        float maxSliderValue = self.pitchShiftSlider.maximumValue;
                        if(nextSliderValue <= maxSliderValue){
                            [self.pitchShiftSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changePitchValue:nextSliderValue];
                            
                        }
                        else {
                            [self.pitchShiftSlider setValue:maxSliderValue animated:YES];
                            [self.effectsModel changePitchValue:maxSliderValue];
                            
                        }
                    }
                    else if(Data == 20){
                        float nextSliderValue = self.pitchShiftSlider.value-20;
                        float minSliderValue = self.pitchShiftSlider.minimumValue;
                        if(nextSliderValue >= minSliderValue){
                            [self.pitchShiftSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changePitchValue:nextSliderValue];
                            
                        }
                        else {
                            [self.pitchShiftSlider setValue:minSliderValue animated:YES];
                            [self.effectsModel changePitchValue:minSliderValue];
                            
                        }
                    }
                    else if(Data == 30){
                        float nextSliderValue = self.pitchShiftSlider.value+50;
                        float maxSliderValue = self.pitchShiftSlider.maximumValue;
                        if(nextSliderValue <= maxSliderValue){
                            [self.pitchShiftSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changePitchValue:nextSliderValue];
                            
                        }
                        else {
                            [self.pitchShiftSlider setValue:maxSliderValue animated:YES];
                            [self.effectsModel changePitchValue:maxSliderValue];
                            
                        }
                    }
                    
                    else if(Data == 40){
                        float nextSliderValue = self.pitchShiftSlider.value-50;
                        float minSliderValue = self.pitchShiftSlider.minimumValue;
                        if(nextSliderValue >= minSliderValue){
                            [self.pitchShiftSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changePitchValue:nextSliderValue];
                            
                        }
                        else {
                            [self.pitchShiftSlider setValue:minSliderValue animated:YES];
                            [self.effectsModel changePitchValue:minSliderValue];
                            
                        }
                    }
                    
                    else if(Data == 50){
                        float nextSliderValue = self.lowpassSlider.value+0.06;
                        float maxSliderValue = self.lowpassSlider.maximumValue;
                        if(nextSliderValue <= maxSliderValue){
                            [self.lowpassSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeLowpassValue:powf(10.0, nextSliderValue)];
                            
                        }
                        else {
                            [self.lowpassSlider setValue:maxSliderValue animated:YES];
                            [self.effectsModel changeLowpassValue:powf(10.0, maxSliderValue)];
                        }
                    }
                    else if(Data == 60){
                        float nextSliderValue = self.lowpassSlider.value-0.06;
                        float minSliderValue = self.lowpassSlider.minimumValue;
                        if(nextSliderValue >= minSliderValue){
                            [self.lowpassSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeLowpassValue:powf(10.0, nextSliderValue)];
                            
                            
                        }
                        else {
                            [self.lowpassSlider setValue:minSliderValue animated:YES];
                            [self.effectsModel changeLowpassValue:powf(10.0, minSliderValue)];
                        }
                    }
                    else if(Data == 70){
                        float nextSliderValue = self.lowpassSlider.value+0.15;
                        float maxSliderValue = self.lowpassSlider.maximumValue;
                        if(nextSliderValue <= maxSliderValue){
                            [self.lowpassSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeLowpassValue:powf(10.0, nextSliderValue)];
                            
                        }
                        else {
                            [self.lowpassSlider setValue:maxSliderValue animated:YES];
                            [self.effectsModel changeLowpassValue:powf(10.0, maxSliderValue)];
                        }
                    }
                    
                    else if(Data == 80){
                        float nextSliderValue = self.lowpassSlider.value-0.15;
                        float minSliderValue = self.lowpassSlider.minimumValue;
                        if(nextSliderValue >= minSliderValue){
                            [self.lowpassSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeLowpassValue:powf(10.0, nextSliderValue)];
                            
                        }
                        else {
                            [self.lowpassSlider setValue:minSliderValue animated:YES];
                            [self.effectsModel changeLowpassValue:powf(10.0, minSliderValue)];
                        }
                    }
                    
                    else if(Data == 90){
                        float nextSliderValue = self.highpassSlider.value+0.06;
                        float maxSliderValue = self.highpassSlider.maximumValue;
                        if(nextSliderValue <= maxSliderValue){
                            [self.highpassSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeHighpassValue:powf(10.0, nextSliderValue)];
                            
                        }
                        else {
                            [self.highpassSlider setValue:maxSliderValue animated:YES];
                            [self.effectsModel changeHighpassValue:powf(10.0, maxSliderValue)];
                        }
                    }
                    else if(Data == 100){
                        float nextSliderValue = self.highpassSlider.value-0.06;
                        float minSliderValue = self.highpassSlider.minimumValue;
                        if(nextSliderValue >= minSliderValue){
                            [self.highpassSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeHighpassValue:powf(10.0, nextSliderValue)];
                            
                            
                        }
                        else {
                            [self.highpassSlider setValue:minSliderValue animated:YES];
                            [self.effectsModel changeHighpassValue:powf(10.0, minSliderValue)];
                        }
                    }
                    else if(Data == 110){
                        float nextSliderValue = self.highpassSlider.value+0.15;
                        float maxSliderValue = self.highpassSlider.maximumValue;
                        if(nextSliderValue <= maxSliderValue){
                            [self.highpassSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeHighpassValue:powf(10.0, nextSliderValue)];
                            
                        }
                        else {
                            [self.highpassSlider setValue:maxSliderValue animated:YES];
                            [self.effectsModel changeHighpassValue:powf(10.0, maxSliderValue)];
                        }
                    }
                    
                    else if(Data == 120){
                        float nextSliderValue = self.highpassSlider.value-0.15;
                        float minSliderValue = self.highpassSlider.minimumValue;
                        if(nextSliderValue >= minSliderValue){
                            [self.highpassSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeHighpassValue:powf(10.0, nextSliderValue)];
                            
                        }
                        else {
                            [self.highpassSlider setValue:minSliderValue animated:YES];
                            [self.effectsModel changeHighpassValue:powf(10.0, minSliderValue)];
                        }
                    }
                }
                else if( self.function == 1 ){
                    if(Data == 10){
                        float nextSliderValue = self.delayFeedbackSlider.value+2.4;
                        float maxSliderValue = self.delayFeedbackSlider.maximumValue;
                        if(nextSliderValue <= maxSliderValue){
                            [self.delayFeedbackSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeDelayFeedback:nextSliderValue];
                            
                        }
                        else {
                            [self.delayFeedbackSlider setValue:maxSliderValue animated:YES];
                            [self.effectsModel changeDelayFeedback:maxSliderValue];
                            
                        }
                    }
                    else if(Data == 20){
                        float nextSliderValue = self.delayFeedbackSlider.value-2.4;
                        float minSliderValue = self.delayFeedbackSlider.minimumValue;
                        if(nextSliderValue >= minSliderValue){
                            [self.delayFeedbackSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeDelayFeedback:nextSliderValue];
                            
                        }
                        else {
                            [self.delayFeedbackSlider setValue:minSliderValue animated:YES];
                            [self.effectsModel changeDelayFeedback:minSliderValue];
                            
                        }
                    }
                    else if(Data == 30){
                        float nextSliderValue = self.delayFeedbackSlider.value+5;
                        float maxSliderValue = self.delayFeedbackSlider.maximumValue;
                        if(nextSliderValue <= maxSliderValue){
                            [self.delayFeedbackSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeDelayFeedback:nextSliderValue];
                            
                        }
                        else {
                            [self.delayFeedbackSlider setValue:maxSliderValue animated:YES];
                            [self.effectsModel changeDelayFeedback:maxSliderValue];
                            
                        }
                    }
                    
                    else if(Data == 40){
                        float nextSliderValue = self.delayFeedbackSlider.value-5;
                        float minSliderValue = self.delayFeedbackSlider.minimumValue;
                        if(nextSliderValue >= minSliderValue){
                            [self.delayFeedbackSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeDelayFeedback:nextSliderValue];
                            
                        }
                        else {
                            [self.delayFeedbackSlider setValue:minSliderValue animated:YES];
                            [self.effectsModel changeDelayFeedback:minSliderValue];
                            
                        }
                    }
                    
                    else if(Data == 50){
                        float nextSliderValue = self.delayTimeSlider.value+0.12;
                        float maxSliderValue = self.delayTimeSlider.maximumValue;
                        if(nextSliderValue <= maxSliderValue){
                            [self.delayTimeSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeDelayTime:nextSliderValue*1.5];
                        }
                        else {
                            [self.delayTimeSlider setValue:maxSliderValue animated:YES];
                            [self.effectsModel changeDelayTime:maxSliderValue*1.5];
                        }
                    }
                    else if(Data == 60){
                        float nextSliderValue = self.delayTimeSlider.value-0.12;
                        float minSliderValue = self.delayTimeSlider.minimumValue;
                        if(nextSliderValue >= minSliderValue){
                            [self.delayTimeSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeDelayTime:nextSliderValue*1.5];
                            
                            
                        }
                        else {
                            [self.delayTimeSlider setValue:minSliderValue animated:YES];
                            [self.effectsModel changeDelayTime:minSliderValue*1.5];
                        }
                    }
                    else if(Data == 70){
                        float nextSliderValue = self.delayTimeSlider.value+0.3;
                        float maxSliderValue = self.delayTimeSlider.maximumValue;
                        if(nextSliderValue <= maxSliderValue){
                            [self.delayTimeSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeDelayTime:nextSliderValue*1.5];
                            
                        }
                        else {
                            [self.delayTimeSlider setValue:maxSliderValue animated:YES];
                            [self.effectsModel changeDelayTime:maxSliderValue*1.5];
                        }
                    }
                    
                    else if(Data == 80){
                        float nextSliderValue = self.delayTimeSlider.value-0.3;
                        float minSliderValue = self.delayTimeSlider.minimumValue;
                        if(nextSliderValue >= minSliderValue){
                            [self.delayTimeSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeDelayTime:nextSliderValue*1.5];
                            
                        }
                        else {
                            [self.delayTimeSlider setValue:minSliderValue animated:YES];
                            [self.effectsModel changeDelayTime:minSliderValue*1.5];
                        }
                    }
                    
                    else if(Data == 90){
                        float nextSliderValue = self.delayWetSlider.value+1;
                        float maxSliderValue = self.delayWetSlider.maximumValue;
                        if(nextSliderValue <= maxSliderValue){
                            [self.delayWetSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeDelayWet:nextSliderValue];
                            
                        }
                        else {
                            [self.delayWetSlider setValue:maxSliderValue animated:YES];
                            [self.effectsModel changeDelayWet:maxSliderValue];
                        }
                    }
                    else if(Data == 100){
                        float nextSliderValue = self.delayWetSlider.value-1;
                        float minSliderValue = self.delayWetSlider.minimumValue;
                        if(nextSliderValue >= minSliderValue){
                            [self.delayWetSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeDelayWet:nextSliderValue];
                            
                            
                        }
                        else {
                            [self.delayWetSlider setValue:minSliderValue animated:YES];
                            [self.effectsModel changeDelayWet:minSliderValue];
                        }
                    }
                    else if(Data == 110){
                        float nextSliderValue = self.delayWetSlider.value+2.2;
                        float maxSliderValue = self.delayWetSlider.maximumValue;
                        if(nextSliderValue <= maxSliderValue){
                            [self.delayWetSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeDelayWet:nextSliderValue];
                            
                        }
                        else {
                            [self.delayWetSlider setValue:maxSliderValue animated:YES];
                            [self.effectsModel changeDelayWet:maxSliderValue];
                        }
                    }
                    
                    else if(Data == 120){
                        float nextSliderValue = self.delayWetSlider.value-2.2;
                        float minSliderValue = self.delayWetSlider.minimumValue;
                        if(nextSliderValue >= minSliderValue){
                            [self.delayWetSlider setValue:nextSliderValue animated:YES];
                            [self.effectsModel changeDelayWet:nextSliderValue];
                            
                        }
                        else {
                            [self.delayWetSlider setValue:minSliderValue animated:YES];
                            [self.effectsModel changeDelayWet:minSliderValue];
                        }
                    }
                    
                }
                
                break;
            }
            default:
                break;
        }
    }
    //    self.packetSizeLabel.text = [NSString stringWithFormat:@"%d",length];
}


@end
