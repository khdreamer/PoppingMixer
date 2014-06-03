//
//  PoppingMixerViewController.h
//  PoppingMixer
//
//  Created by Kevin Huang on 2014/6/3.
//  Copyright (c) 2014年 NMLab Project. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface PoppingMixerViewController : UIViewController


@property (weak, nonatomic) IBOutlet UIButton *touchMeButton;
- (IBAction)addBeat:(id)sender;

@end
