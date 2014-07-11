//
//  MyScene.h
//  ClientiOS
//

//  Copyright (c) 2014 zachmetcalf. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>

enum ClientState
{
    State_Initial = 1 << 0,
    State_Waiting_For_ServerIP = 1 << 1,
    State_Waiting_For_ServerPort = 1 << 2,
    State_Waiting_For_PublishTopic = 1 << 3,
    State_Waiting_For_SubscribeTopic = 1 << 4,
    State_Setting_Up_Client = 1 << 5,
    State_Client_Running = 1 << 6,
};

struct ClientObjC;


@interface MyScene : SKScene <UITextFieldDelegate>
{
    struct ClientObjC* clientObjC;
    
    enum ClientState mClientState;
    
    float mLabelScale;
    int mTimesMoved;
    int mCountVisibleLabels;
}

@property (nonatomic, retain) UITextField *textField;
@property (nonatomic, retain) NSMutableArray* mLabelArray;

-(void)didMoveToView:(SKView*)view;

-(void)SetState:(enum ClientState)inClientState;
-(void)ProcessTextInput:(NSString*)inString;
-(void)AddLabel:(NSString*)inText;

+(id)SharedSceneWithSize:(CGSize)size;

@end
