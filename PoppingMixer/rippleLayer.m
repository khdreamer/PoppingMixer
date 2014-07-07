//
//  rippleLayer.m
//  PoppingMixer
//
//  Created by Apple on 2014/7/6.
//  Copyright (c) 2014年 NMLab Project. All rights reserved.
//

#import "rippleLayer.h"

@implementation rippleLayer

-(id)init {
    self = [super init];
    if (self) {
//        self.path = CGPathCreateWithEllipseInRect(CGRectMake(0, 0, 50, 50), 0);
        self.strokeColor = [UIColor whiteColor].CGColor;
        self.fillColor = [UIColor clearColor].CGColor;
        self.lineWidth = 10;
        self.lineCap = kCALineCapRound;
//        self.strokeEnd=0.001;
    }
    return self;
}

-(void) computePath:(CGRect)r {
    float length = self.bounds.size.width/2;
    self.path = [UIBezierPath bezierPathWithArcCenter:CGPointMake(length, length) radius: length-5 startAngle:0 endAngle:M_PI*2 clockwise:YES].CGPath;
}

-(void) runAnimation {
    
    
    
    /*
    float advance=0.1;
    if (self.strokeEnd>1) self.strokeEnd=0;
    
    CABasicAnimation * swipe = [CABasicAnimation animationWithKeyPath:@"strokeEnd"];
    swipe.duration = 0.25;
    swipe.fromValue=[NSNumber numberWithDouble:self.strokeEnd];
    swipe.toValue=  [NSNumber numberWithDouble:self.strokeEnd + advance];
    
    swipe.fillMode = kCAFillModeForwards;
    swipe.timingFunction= [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    swipe.removedOnCompletion = YES;
    self.strokeEnd = self.strokeEnd + advance;
    [self addAnimation:swipe forKey:@"strokeEnd animation"];
     */
}


@end
