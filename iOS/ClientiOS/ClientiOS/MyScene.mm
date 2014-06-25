//
//  MyScene.mm
//  ClientiOS
//
//  Created by Zach Metcalf on 6/24/14.
//  Copyright (c) 2014 zachmetcalf. All rights reserved.
//

#import "MyScene.h"

#include <TCPLibrary.h>




struct ClientObjC
{
    TCPLibrary::Client client;
    std::string ClientIP;
    std::string ServerIP;
    std::string ServerPort;
    
    //TCPLibrary::CallBack callBack;
};


static MyScene *sharedSceneInstance;

static NSString* cppString;
static bool shouldWrite = false;


@implementation MyScene

+ (id)SharedSceneWithSize:(CGSize)size
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
        
        
        
        
        
        
        
        self.LabelScale = 18.0f;
        self.timesMoved = 0.0f;
        
        
        [self SetState:State_Initial];
        
        
        //sharedSceneInstance = self;
        
    }
    return self;
}


-(void)didMoveToView:(SKView *)view
{
    self.textField = [[UITextField alloc] initWithFrame:CGRectMake(self.size.width/2 + 100, self.size.height/2 - 50, 200, 40)];
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


-(void)addLabel:(NSString*)inText
{
    if(self.mLabelArray.count > 7)
    {
        for(UILabel* label in self.mLabelArray)
        {
            float newX = label.frame.origin.x;
            float newY = label.frame.origin.y - self.LabelScale;
            
            CGRect newRect = CGRectMake(newX, newY, 400, 40);
            
            [UIView transitionWithView:label duration:1.00f options:UIViewAnimationCurveEaseInOut
                            animations:^(void) { label.frame = newRect; }
                            completion:^(BOOL finished) { }
             ];
        }
        
        self.timesMoved++;
    }
    
    
    
    NSUInteger offset = self.mLabelArray.count - self.timesMoved;
    
    UILabel *myLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 10 + (offset * self.LabelScale), 400, 40)];
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
    if(mClientState & State_Waiting_For_ClientIP)
    {
        std::string inClientIP([inString UTF8String]);
        clientObjC->ClientIP = inClientIP;
        
        [self addLabel:[NSString stringWithFormat:@"ClientIP: %@", inString]];
        [self SetState:State_Waiting_For_ServerIP];
    }
    else if(mClientState & State_Waiting_For_ServerIP)
    {
        std::string inServerIP([inString UTF8String]);
        clientObjC->ServerIP = inServerIP;
        
        [self addLabel:[NSString stringWithFormat:@"ServerIP: %@", inString]];
        [self SetState:State_Waiting_For_ServerPort];
    }
    else if(mClientState & State_Waiting_For_ServerPort)
    {
        std::string inServerPort([inString UTF8String]);
        clientObjC->ServerPort = inServerPort;
        
        [self addLabel:[NSString stringWithFormat:@"ServerPort: %@", inString]];
        [self SetState:State_Setting_Up_Client];
    }
    else if(mClientState & State_Client_Running)
    {
        // Client Publisher
        if (clientObjC->client.GetIsClientRunning())
        {
            // Reset Output Message
            //NSString* inText = textField.text;
            std::string messageToSend([inString UTF8String]);
            
            // Publish Message
            clientObjC->client.Publish(messageToSend);
            [self addLabel:[NSString stringWithFormat:@"sent: %@", inString]];
            
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
    //NSLog(@"State = %d", mClientState);
    
    
    if(mClientState == State_Initial || mClientState == State_Setting_Up_Client)
    {
        self.textField.text = @" ";
        self.textField.placeholder = @" ";
    }
    else if(mClientState == State_Waiting_For_ClientIP)
    {
        self.textField.text = @"";
        self.textField.placeholder = @"Enter ClientIP:";
    }
    else if(mClientState == State_Waiting_For_ServerIP)
    {
        //self.textField.text = @"Enter ServerIP:";
        self.textField.placeholder = @"Enter ServerIP:";
        self.textField.text = @"";
    }
    else if(mClientState & State_Waiting_For_ServerPort)
    {
        //self.textField.text = @"Enter ServerPort:";
        self.textField.placeholder = @"Enter ServerPort:";
        self.textField.text = @"";
    }
    else
    {
        self.textField.text = @"";
        self.textField.placeholder = @"Enter Text:";
    }
}








void SubscriberCallback(const std::string& inString)
{
    std::cout << "recv: " << inString << std::endl;
    
    //MyScene* scene = [MyScene SharedSceneWithSize:CGSizeZero];
    MyScene* scene = sharedSceneInstance;
    
    //NSString* outString = [NSString stringWithUTF8String:inString.c_str()];
    NSString* outString = [[NSString alloc] initWithUTF8String:inString.c_str()];
    
    
    NSString* outString2 = [NSString stringWithFormat:@"recv: %@", outString];
    
    
    cppString = outString2;
    shouldWrite = true;
    
    
    //[scene addLabel:outString2];
}





-(void)update:(CFTimeInterval)currentTime
{
    
    
    if(mClientState & State_Initial)
    {
        // Create Client
        clientObjC = new ClientObjC;
        clientObjC->client = TCPLibrary::Client();
        
        [self addLabel:[NSString stringWithFormat:@"Creating Client"]];
        [self SetState:State_Waiting_For_ClientIP];
    }
    else if(mClientState & State_Setting_Up_Client)
    {
        //clientObjC->client.Setup(std::string("127.0.0.1"), std::string("127.0.0.1"), std::string("45000"));
        clientObjC->client.Setup(clientObjC->ClientIP, clientObjC->ServerIP, clientObjC->ServerPort);
        [self addLabel:[NSString stringWithFormat:@"Client Connected to Server"]];
        
        // Client Subscriber and Default CallBack
        //clientObjC->client.Subscribe(nullptr);
        // Client Subscriber and Custom CallBack
        TCPLibrary::CallBack callBack = &SubscriberCallback;
        clientObjC->client.Subscribe(callBack);
        // Client Subscriber with No Publisher
        //while (clientObjC->client.GetIsClientRunning()) {}
        
        
        [self SetState:State_Client_Running];
    }
    
    if(shouldWrite)
    {
        shouldWrite = false;
        [self addLabel:cppString];
    }
}

@end
