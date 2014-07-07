//
//  rippleLayer.h
//  PoppingMixer
//
//  Created by Apple on 2014/7/6.
//  Copyright (c) 2014年 NMLab Project. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

@interface rippleLayer : CAShapeLayer

-(void) runAnimation;
-(void) computePath:(CGRect)r;

@end
