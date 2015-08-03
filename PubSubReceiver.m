//
//  PubSubReceiver.m
//  PubSubPlugin
//
//  Created by Kristal on 29/07/2015.
//  Copyright (c) 2015 Kristal. All rights reserved.
//

#import "PubSubReceiver.h"

@implementation PubSubReceiver

/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma mark INIT

/////////////////////////////////////////////////////////////////////////////////////////////////

- (id)initWithViewController:(CobaltViewController *)viewController {
    if (self = [super init]) {
        _viewController = viewController;
        callbackForChannel = [NSMutableDictionary dictionary];
    }
    
    return self;
}

- (id)initWithViewController:(CobaltViewController *)viewController
                 andCallback:(NSString *)callback
                  forChannel:(NSString *)channel {
    if (self = [super init]) {
        _viewController = viewController;
        callbackForChannel = [NSMutableDictionary dictionaryWithDictionary:@{channel: callback}];
    }
    
    return self;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma mark HELPERS

/////////////////////////////////////////////////////////////////////////////////////////////////

- (void)subscribeToChannel:(NSString *)channel
              withCallback:(NSString *)callback {
    NSAssert(channel, @"Cannot subscribe for a nil channel.");
    
    [callbackForChannel setObject:callback
                           forKey:channel];
}

- (void)unsubscribeFromChannel:(NSString *)channel {
    NSAssert(channel, @"Cannot unsubscribe from a nil channel.");
    
    [callbackForChannel removeObjectForKey:channel];
    
    if (! callbackForChannel.count
        && _delegate) {
        [_delegate receiverReadyForRemove:self];
    }
}

- (void)receiveMessage:(NSDictionary *)message
            forChannel:(NSString *)channel {
    if (! _viewController) {
        NSLog(@"PubSubReceiver receiveMessage:forChannel: - viewController is nil. \
              It may be caused by its deallocation or the PubSubReceiver was not correctly initialized... \
              Please check if the PubSubReceiver has been initialized with initWithViewController: or initWithViewController:andCallback:forChannel: methods.");
    
        if (_delegate) {
            [_delegate receiverReadyForRemove:self];
            return;
        }
    }

    NSAssert(channel, @"Cannot send message to nil channel");
    
    NSString *callback = [callbackForChannel objectForKey:channel];
    if (! callback) {
        NSLog(@"PubSubReceiver receiveMessage:forChannel: - %@ has not subscribed to %@ channel yet or has already unsubscribed.", [_viewController class], channel);
        return;
    }
    
    [_viewController sendCallback:callback
                        withData:message];
}

@end
