//
//  PubSubPlugin.h
//  PubSubPlugin
//
//  Created by Kristal on 06/01/15.
//  Copyright (c) 2015 Kristal. All rights reserved.
//

#import "CobaltAbstractPlugin.h"

#import "PubSubReceiver.h"

/**
 * A plugin which allow UIWebViews contained in CobaltViewController to broadcast messages between them into channels.
 * Handles subscribe/unsubscribe to channel events and publish message event.
 * Broadcasts messages to UIWebViews which have subscribed to the channel where they are from.
 */
@interface PubSubPlugin : CobaltAbstractPlugin <PubSubReceiverDelegate> {
    /**
     * The array which keeps track of PubSubReceivers
     */
    NSMutableArray *receivers;
}

@end
