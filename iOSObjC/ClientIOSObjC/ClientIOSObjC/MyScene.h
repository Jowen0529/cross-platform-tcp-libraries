//
//  MyScene.h
//  ClientIOSObjC
//

//  Copyright (c) 2014 zachmetcalf. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>


struct ClientObjC;



enum ClientState
{
    State_Initial = 1 << 0,
    State_Waiting_For_ClientIP = 1 << 1,
    State_Waiting_For_ServerIP = 1 << 2,
    State_Waiting_For_ServerPort = 1 << 3,
    State_Setting_Up_Client = 1 << 4,
    State_Client_Running = 1 << 5,
};



@interface MyScene : SKScene <UITextFieldDelegate>
{
    enum ClientState mClientState;
    
@public
    struct ClientObjC* clientObjC;
}

-(void)didMoveToView:(SKView *)view;


-(void)ProcessTextInput:(NSString*)inString;


-(void)SetState:(enum ClientState)inClientState;


@property (nonatomic, retain) NSMutableArray* mLabelArray;
-(void)addLabel:(NSString*)inText;

@property (nonatomic, retain) UITextField *textField;


@property float LabelScale;
@property float timesMoved;


//+(id)SharedScene;
+(id)SharedSceneWithSize:(CGSize)size;

//@property enum ClientState mClientState;






@end

