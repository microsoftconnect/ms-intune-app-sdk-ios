//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

@interface IntuneMAMUIHelper : NSObject

// Shows an alert displaying an error message to the user, indicated that the requested sharing action
// was blocked. Call this method instead of performing the sharing action when isSaveToAllowedForLocation
// or isOpenFromAllowedForLocation returned false.
+ (void) showSharingBlockedMessage:(void(^_Nullable)(void))completion;

@end
