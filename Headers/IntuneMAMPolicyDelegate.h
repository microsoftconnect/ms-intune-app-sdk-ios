//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IntuneMAMAsyncResult.h"

@protocol IntuneMAMPolicyDelegate <NSObject>

typedef enum IntuneMAMIdentitySwitchReason
{
    IntuneMAMIdentitySwitchOpenURL,
    IntuneMAMIdentitySwitchCancelConditionalLaunch
} IntuneMAMIdentitySwitchReason;

@optional

// Called by the Intune SDK to inform the application an identity switch is required.
// The application should respond with IntuneMAMSwitchIdentitySuccess if the SDK
// is allowed to switch to the specified identity, otherwise IntuneMAMSwitchIdentityFailed.
// The SDK will block the operation which required the identity
// switch until the application sets the result value. This method may also be
// called in response to a user clicking the 'cancel' button on the PIN or
// Authentication UI after an application resume.
// The application does not have to call setUIPolicyIdentity in response to this call.
- (void) identitySwitchRequired:(NSString*)identity reason:(IntuneMAMIdentitySwitchReason)reason withAsyncResult:(id<IntuneMAMAsyncResult>)result;


// Called by the Intune SDK when the application should wipe data for the
// specified account user principal name (e.g. user@contoso.com).
// Returns TRUE if successful, FALSE if the account data could not be completely wiped.
- (BOOL) wipeDataForAccount:(NSString*)upn;


// Called by the Intune SDK when the application needs to restart
// because policy has been received for the first time.  This method
// is called on a background thread.
// Returns TRUE if the host application will restart on its own.
// Returns FALSE if the host application wants the Intune SDK to handle the restart
- (BOOL) restartApplication;

// Called by the Intune SDK when the application needs to add an user account as the app has been
// automatically enrolled by the SDK. The result value should be set to
// IntuneMAMAddIdentitySuccess if the app is able to add the identity, IntuneMAMAddIdentityFailed if otherwise.
- (void) addIdentity:(NSString*)identity withAsyncResult:(id<IntuneMAMAsyncResult>)result;

@end
