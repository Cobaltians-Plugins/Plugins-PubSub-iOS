//
//  PubSubReceiver.h
//  PubSubPlugin
//
//  Created by Kristal on 29/07/2015.
//  Copyright (c) 2015 Kristal. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CobaltViewController.h"

@class PubSubReceiver;

/**
 * A protocol to implement to be notified when a PubSubReceiver viewController is nil (deallocated or not correctly initialized)
 * or a PubSubReceiver is not subscribed to any channel any more
 */
@protocol PubSubReceiverDelegate <NSObject>

@required

/**
 * @discussion Notifies when a PubSubReceiver viewController is nil (deallocated or not correctly initialized)
 * or a PubSubReceiver is not subscribed to any channel any more
 * @param receiver the PubSubReceiver
 */
- (void)receiverReadyForRemove:(PubSubReceiver *)receiver;

@end

/**
 * An object allowing a UIWebView contained in a CobaltViewController to subscribe/unsubscribe for messages sent via a channel and receive them.
 */
@interface PubSubReceiver : NSObject {
    /**
     * The dictionary which keeps track of subscribed channels and their linked callback
     */
    NSMutableDictionary *callbackForChannel;
}

///////////////////////////////////////////////////////////////////////////

#pragma mark PROPERTIES

///////////////////////////////////////////////////////////////////////////

/**
 * The CobaltViewController containing the UIWebView to which send messages
 */
@property (weak, nonatomic, readonly) CobaltViewController *viewController;
/**
 * The delegate to notify when the viewController is nil (deallocated or not correctly initialized)
 * or the PubSubReceiver is not subscribed to any channel any more
 */
@property (weak, nonatomic) id <PubSubReceiverDelegate> delegate;

///////////////////////////////////////////////////////////////////////////

#pragma mark METHODS

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

#pragma mark Init

///////////////////////////////////////////////////////////////////////////

/**
 * @discussion Creates and return a PubSubReceiver for the specified CobaltViewController registered to no channel.
 * @param viewController the CobaltViewController containing the UIWebView to which send messages.
 * @return A new PubSubReceiver for the specified CobaltViewController registered to no channel.
 */
- (id)initWithViewController:(CobaltViewController *)viewController;
/**
 * @discussion Creates and return a PubSubReceiver for the specified CobaltViewController registered to the specified channel.
 * @param viewController the CobaltViewController containing the UIWebView to which send messages.
 * @param callback the callback to call to forward messages from the specified channel.
 * @param channel the channel from which the messages will come from.
 * @return A new PubSubReceiver for the specified CobaltViewController registered to the specified channel.
 */
- (id)initWithViewController:(CobaltViewController *)viewController
                 andCallback:(NSString *)callback
                  forChannel:(NSString *)channel;

///////////////////////////////////////////////////////////////////////////

#pragma mark Helpers

///////////////////////////////////////////////////////////////////////////

/**
 * @discussion Subscribes to messages sent from the specified channel.
 * @warning overrides the callback if the PubSubReceiver has already subscribed to the specified channel
 * @param callback the callback to call to forward messages from the specified channel.
 * @param channel the channel from which the messages will come from.
 */
- (void)subscribeToChannel:(NSString *)channel
              withCallback:(NSString *)callback;
/**
 * @discussion Unsubscribes from messages sent from the specified channel.
 * @warning if after the unsubscription, the PubSubReceiver is not subscribed to any channel and delegate is set, 
 * its receiverReadyForRemove: method will be called.
 * @param channel the channel from which the messages come from.
 */
- (void)unsubscribeFromChannel:(NSString *)channel;

/**
 * @discussion If the PubSubReceiver has subscribed to the specified channel, sends the specified message from this channel to the UIWebView contained in the viewController
 * @warning if viewController is nil at this time, due to deallocation or wrong initialization, 
 * and the delegate is set, its receiverReadyForRemove: method will be called.
 * @param message the message received from the channel.
 * @param channel the channel from which the messages come from.
 */
- (void)receiveMessage:(NSDictionary *)message
            forChannel:(NSString *)channel;

@end
