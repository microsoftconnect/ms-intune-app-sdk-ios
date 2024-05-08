//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IntuneMAMAppConfig.h"


// Notification name for MAM service App Configuration change notifications.
// Applications can register for notifications using the default NSNotificationCenter.
// The NSNotification passed to the observer will contain the IntuneMAMAppConfigManager instance
// as the object.
__attribute__((visibility("default")))
extern NSString* _Nonnull const IntuneMAMAppConfigDidChangeNotification;

// UserInfo dictionary constants.
__attribute__((visibility("default")))
extern NSString*_Nonnull const IntuneMAMAppConfigDidChangeNotificationAccountId;

__attribute__((visibility("default")))
@interface IntuneMAMAppConfigManager : NSObject

+ (IntuneMAMAppConfigManager*_Nonnull) instance;

// Returns an object that can be used to retrieve Application Configuration
// settings sent from the MAM service/MDM channel for the specified identity.
// Note: For any MDM settings to be returned the given identity must be the identity of the MDM enrolled user
-(id <IntuneMAMAppConfig> _Nonnull) appConfigForIdentity:(NSString*_Nullable)identity;

// Returns an object that can be used to retrieve Application Configuration
// settings sent from the MAM service/MDM channel for the specified identity.
// Note: For any MDM settings to be returned the given AccountId (e.g. 3ec2c00f-b125-4519-acf0-302ac3761822) must be the AccountId of the MDM enrolled user
-(id <IntuneMAMAppConfig> _Nonnull) appConfigForAccountId:(NSString*_Nullable)accountId;

@end
