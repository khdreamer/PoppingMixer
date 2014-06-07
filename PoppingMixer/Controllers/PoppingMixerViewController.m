//
//  PoppingMixerViewController.m
//  PoppingMixer
//
//  Created by Kevin Huang on 2014/6/3.
//  Copyright (c) 2014年 NMLab Project. All rights reserved.
//

#import "PoppingMixerViewController.h"
#import "AudioModel.h"

@interface PoppingMixerViewController ()

@property (nonatomic, strong) AudioModel *audioModel;

@end

@implementation PoppingMixerViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
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
    [self.audioModel playNote:24 withGain:200];
    
}
@end
