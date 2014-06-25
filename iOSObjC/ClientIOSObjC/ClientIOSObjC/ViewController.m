//
//  ViewController.m
//  ClientIOSObjC
//
//  Created by Zach Metcalf on 6/24/14.
//  Copyright (c) 2014 zachmetcalf. All rights reserved.
//

#import "ViewController.h"
#import "MyScene.h"

@implementation ViewController

/*
-(void)viewDidLoad
{
    [super viewDidLoad];
*/
    
-(void)viewWillLayoutSubviews
{
    [super viewWillLayoutSubviews];
 

    // Configure the view.
    SKView * skView = (SKView *)self.view;
    skView.showsFPS = YES;
    skView.showsNodeCount = YES;
    
    // Create and configure the scene.
    
    
    //SKScene * scene = [MyScene sceneWithSize:skView.bounds.size];
    SKScene* scene = [MyScene SharedSceneWithSize:skView.bounds.size];
    scene.scaleMode = SKSceneScaleModeAspectFill;
    
    
    // Present the scene.
    [skView presentScene:scene];
}

- (BOOL)shouldAutorotate
{
    return YES;
}

- (NSUInteger)supportedInterfaceOrientations
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return UIInterfaceOrientationMaskAllButUpsideDown;
    } else {
        return UIInterfaceOrientationMaskAll;
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

@end
