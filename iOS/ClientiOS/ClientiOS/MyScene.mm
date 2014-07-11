//
//  MyScene.mm
//  ClientiOS
//
//  Created by Zach Metcalf on 6/24/14.
//  Copyright (c) 2014 zachmetcalf. All rights reserved.
//

#import "MyScene.h"

// TCP Library
#include <TCPLibrary.h>

struct ClientObjC
{
    TCPLibrary::Client client;
    std::string ServerIP;
    std::string ServerPort;
    std::string PublishTopic;
    std::string SubscribeTopic;
};


static NSString* CallBackString;
static bool IsCallBackStringAvailable = false;

static MyScene *sharedSceneInstance;

@implementation MyScene

+(id)SharedSceneWithSize:(CGSize)size
{
    @synchronized(self)
    {
        if (sharedSceneInstance == nil)
        {
            sharedSceneInstance = [[self alloc] initWithSize:size];
        }
    }
    return sharedSceneInstance;
}


-(id)initWithSize:(CGSize)size
{
    if (self = [super initWithSize:size])
    {
        self.backgroundColor = [SKColor colorWithRed:0.10 green:0.50 blue:0.80 alpha:0.90];
        
        self.mLabelArray = [[NSMutableArray alloc] init];
        mLabelScale = 18.0f;
        mTimesMoved = 0;
        mCountVisibleLabels = 7;
        
        [self SetState:State_Initial];
    }
    return self;
}


-(void)didMoveToView:(SKView *)view
{
    self.textField = [[UITextField alloc]
        initWithFrame:CGRectMake(self.size.width/2 + 100, self.size.height/2 - 50, 200, 40)];
    [self.textField setCenter:CGPointMake(self.size.width/2 + 100, self.size.height/2 - 50)];
    
    self.textField.borderStyle = UITextBorderStyleRoundedRect;
    self.textField.textColor = [UIColor blackColor];
    self.textField.font = [UIFont systemFontOfSize:17.0];
    self.textField.placeholder = @" ";
    self.textField.backgroundColor = [UIColor whiteColor];
    self.textField.autocorrectionType = UITextAutocorrectionTypeYes;
    self.textField.keyboardType = UIKeyboardTypeDefault;
    self.textField.clearButtonMode = UITextFieldViewModeWhileEditing;
    self.textField.delegate = self;
    [self.view addSubview:self.textField];
}


-(void)AddLabel:(NSString*)inText
{
    if(self.mLabelArray.count > mCountVisibleLabels)
    {
        for(UILabel* label in self.mLabelArray)
        {
            float newX = label.frame.origin.x;
            float newY = label.frame.origin.y - mLabelScale;
            CGRect newRect = CGRectMake(newX, newY, 400, 40);
            
            [UIView transitionWithView:label duration:1.00f options:UIViewAnimationCurveEaseInOut
                            animations:^(void) { label.frame = newRect; }
                            completion:^(BOOL finished) { }
             ];
        }
        
        mTimesMoved++;
    }

    
    NSUInteger offset = self.mLabelArray.count - mTimesMoved;
    
    UILabel *myLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 10 + (offset * mLabelScale), 400, 40)];
    [myLabel setBackgroundColor:[UIColor clearColor]];
    [myLabel setText:inText];
    
    myLabel.backgroundColor = [UIColor clearColor];
    myLabel.font = [UIFont fontWithName:@"MarkerFelt-Thin" size:16.0];
    
    [self.mLabelArray addObject:myLabel];
    [[self view] addSubview:myLabel];
}


-(BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
    //NSLog(@"textFieldShouldBeginEditing");
    textField.backgroundColor = [UIColor colorWithRed:220.0f/255.0f green:220.0f/255.0f blue:220.0f/255.0f alpha:1.0f];
    return YES;
}


-(BOOL)textFieldShouldReturn:(UITextField *)textField
{
    //NSLog(@"textFieldShouldReturn");
    [textField resignFirstResponder];
    return YES;
}


-(void)textFieldDidBeginEditing:(UITextField *)textField
{
    //NSLog(@"textFieldDidBeginEditing");
}


-(void)textFieldDidEndEditing:(UITextField *)textField
{
    //NSLog(@"textFieldDidEndEditing");
    
    [self ProcessTextInput:textField.text];
}


-(void)ProcessTextInput:(NSString*)inString
{
    if(mClientState & State_Waiting_For_ServerIP)
    {
        std::string inServerIP([inString UTF8String]);
        clientObjC->ServerIP = inServerIP;
        
        [self AddLabel:[NSString stringWithFormat:@"ServerIP: %@", inString]];
        [self SetState:State_Waiting_For_ServerPort];
    }
    else if(mClientState & State_Waiting_For_ServerPort)
    {
        std::string inServerPort([inString UTF8String]);
        clientObjC->ServerPort = inServerPort;
        
        [self AddLabel:[NSString stringWithFormat:@"ServerPort: %@", inString]];
        [self SetState:State_Waiting_For_PublishTopic];
    }
    else if(mClientState & State_Waiting_For_PublishTopic)
    {
        std::string inPublishTopic([inString UTF8String]);
        clientObjC->PublishTopic = inPublishTopic;
        
        [self AddLabel:[NSString stringWithFormat:@"PublishTopic: %@", inString]];
        [self SetState:State_Waiting_For_SubscribeTopic];
    }
    else if(mClientState & State_Waiting_For_SubscribeTopic)
    {
        std::string inSubscribeTopic([inString UTF8String]);
        clientObjC->SubscribeTopic = inSubscribeTopic;
        
        [self AddLabel:[NSString stringWithFormat:@"SubscribeTopic: %@", inString]];
        [self SetState:State_Setting_Up_Client];
    }
    else if(mClientState & State_Client_Running)
    {
        // Client Publisher
        if (clientObjC->client.GetIsClientRunning())
        {
            // Reset Output Message
            std::string messageToSend([inString UTF8String]);
            
            // Publish Message
            clientObjC->client.Publish(messageToSend);
            //[self AddLabel:[NSString stringWithFormat:@"sent: %@", inString]];
            
            if (messageToSend == std::string("quit"))
            {
                clientObjC->client.SetIsClientRunning(false);
                self.textField.enabled = false;
            }
        }
    }
}


-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    
}



-(void)SetState:(enum ClientState)inClientState;
{
    mClientState = inClientState;
    //NSLog(@"State = %d", self.mClientState);
    
    if(mClientState & State_Initial || mClientState & State_Setting_Up_Client)
    {
        self.textField.placeholder = @"";
        self.textField.text = @"";
    }
    else if(mClientState & State_Waiting_For_ServerIP)
    {
        self.textField.placeholder = @"Enter ServerIP:";
        self.textField.text = @"";
    }
    else if(mClientState & State_Waiting_For_ServerPort)
    {
        self.textField.placeholder = @"Enter ServerPort:";
        self.textField.text = @"";
    }
    else if(mClientState & State_Waiting_For_PublishTopic)
    {
        self.textField.placeholder = @"Enter PublishTopic:";
        self.textField.text = @"";
    }
    else if(mClientState & State_Waiting_For_SubscribeTopic)
    {
        self.textField.placeholder = @"Enter SubscribTopic:";
        self.textField.text = @"";
    }
    else
    {
        self.textField.placeholder = @"Enter Text:";
        self.textField.text = @"";
    }
}


void SubscriberCallback(const std::string& inString)
{
    std::cout << "recv: " << inString << std::endl;
    
    NSString* outString = [[NSString alloc] initWithUTF8String:inString.c_str()];
    NSString* outStringFormatted = [NSString stringWithFormat:@"recv: %@", outString];
    
    CallBackString = outStringFormatted;
    IsCallBackStringAvailable = true;
}


-(void)update:(CFTimeInterval)currentTime
{
    if(mClientState & State_Initial)
    {
        // Create Client
        clientObjC = new ClientObjC;
        clientObjC->client = TCPLibrary::Client();
        
        [self AddLabel:[NSString stringWithFormat:@"Creating Client"]];
        [self SetState:State_Waiting_For_ServerIP];
    }
    else if(mClientState & State_Setting_Up_Client)
    {
        clientObjC->client.Setup(clientObjC->ServerIP, clientObjC->ServerPort,
                clientObjC->PublishTopic, clientObjC->SubscribeTopic);
        [self AddLabel:[NSString stringWithFormat:@"Client Connected to Server"]];
        
        
        // Client Subscriber and Default CallBack
        //clientObjC->client.Subscribe(nullptr);
        // Client Subscriber and Custom CallBack
        TCPLibrary::CallBack callBack = &SubscriberCallback;
        clientObjC->client.Subscribe(callBack);
        // Client Subscriber with No Publisher
        //while (clientObjC->client.GetIsClientRunning()) {}
        
        
        [self SetState:State_Client_Running];
    }
    
    
    if(IsCallBackStringAvailable)
    {
        IsCallBackStringAvailable = false;
        [self AddLabel:CallBackString];
    }
}

@end
