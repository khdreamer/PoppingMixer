//
//  RippleView.m
//  PoppingMixer
//
//  Created by Apple on 2014/7/6.
//  Copyright (c) 2014年 NMLab Project. All rights reserved.
//

#import "RippleView.h"
//#import "rippleLayer.h"

@implementation RippleView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
        self.backgroundColor = [UIColor clearColor];
//        rippleLayer *circle = [[rippleLayer alloc] init];
//        [circle computePath:self.bounds];
//        [circle runAnimation];
//        [(rippleLayer *)self.layer addSublayer:circle];
    }
    return self;
}


// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    //Get current context
    CGContextRef mainContext = UIGraphicsGetCurrentContext();
    
    /** Draw the Path **/
    CGContextAddArc(mainContext, self.frame.size.width/2, self.frame.size.height/2, 50, 0, 2*M_PI, 0);
    
    [[UIColor whiteColor]setStroke];
    CGContextSetLineWidth(mainContext, 2);
    CGContextSetLineCap(mainContext, kCGLineCapButt);
    CGContextDrawPath(mainContext, kCGPathStroke);
   
    self.layer.opacity = 0.0;
    
    CABasicAnimation *scaleAnimation = [CABasicAnimation animationWithKeyPath:@"transform.scale"];
//    scaleAnimation.duration = 1.0f;
    scaleAnimation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    scaleAnimation.fromValue = [NSNumber numberWithFloat:0.1];
    scaleAnimation.toValue = [NSNumber numberWithFloat:3.0];
    
    CABasicAnimation *opacityAnimation = [CABasicAnimation animationWithKeyPath:@"opacity"];
    opacityAnimation.fromValue = [NSNumber numberWithFloat:1.0];
    opacityAnimation.toValue = [NSNumber numberWithFloat:0.0];
//    opacityAnimation.duration = 1.0f;
    opacityAnimation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    
    CAAnimationGroup *group = [CAAnimationGroup animation];
    group.duration = 0.5f;
    group.repeatCount = 1;
    group.autoreverses = NO;
    group.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    group.animations = [NSArray arrayWithObjects:scaleAnimation, opacityAnimation, nil];
    group.delegate = self;
    group.removedOnCompletion = NO;
    [self.layer addAnimation:group
                         forKey:@"groupAnimation"];
//    self.layer.actions = [NSDictionary dictionaryWithObject:group forKey:@"groupAnimation"];
    
//    [[UIColor clearColor] setStroke];
//    UIRectFrame(self.bounds);
}

-(void) animationDidStop:(CAAnimation *)anim finished:(BOOL)flag
{
    [self removeFromSuperview];    
}

//+(Class)layerClass {
//    return [rippleLayer class];
//}

@end
