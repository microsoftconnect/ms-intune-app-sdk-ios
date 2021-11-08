//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IntuneMAMUserStatus.h"

// Notification name for Intune User Status change notifications.
// Applications can register for notifications using the default NSNotificationCenter.
// The NSNotification passed to the observer will contain the IntuneMAMUserStatusManager instance as the object
// and userInfo will be nil.
__attribute__((visibility("default"))) extern NSString*_Nonnull const IntuneMAMUserStatusDidChangeNotification;


__attribute__((visibility("default")))
@interface IntuneMAMUserStatusManager : NSObject

+ (IntuneMAMUserStatusManager*_Nonnull) instance;

// Returns an object that can be used to retrieve the user status for the specified identity.
- (_Nullable id<IntuneMAMUserStatus>) userStatusForIdentity:(NSString*_Nullable)identity;

@end
