//
//  VisualEffectView.m
//  PoppingMixer
//
//  Created by Apple on 2014/7/6.
//  Copyright (c) 2014年 NMLab Project. All rights reserved.
//

#import "VisualEffectView.h"

@implementation VisualEffectView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        self.backgroundColor = [UIColor clearColor];
    }
    return self;
}

-(void) drawRippleAtLocation:(CGPoint)location
{
    
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.

- (void)drawRect:(CGRect)rect
{
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    CGContextClearRect(context, self.bounds);
    
    // set color of path and shadow/glow
    CGContextSetLineWidth(context, 15.0);
    CGContextSetStrokeColorWithColor(context, [UIColor colorWithRed:1 green:1 blue:1 alpha:0.5].CGColor);
    CGContextSetShadowWithColor(context, CGSizeMake(0, 0), 15.0, [UIColor whiteColor].CGColor);
    CGContextSetLineCap(context, kCGLineCapRound);
    // put path on
    UIBezierPath *circle = [UIBezierPath bezierPathWithArcCenter:CGPointMake(self.bounds.size.width/2, self.bounds.size.height/2) radius:150 startAngle:0 endAngle:M_PI*2 clockwise:YES];
    CGContextAddPath(context, [circle CGPath]);
    CGContextStrokePath(context);
}


@end
