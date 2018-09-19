//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IntuneMAM/IntuneMAMDefs.h>

typedef NS_ENUM(NSUInteger, IntuneMAMIdentitySwitchReason)
{
    IntuneMAMIdentitySwitchOpenURL,
    IntuneMAMIdentitySwitchCancelConditionalLaunch
};

typedef NS_ENUM(NSUInteger, IntuneMAMAddIdentityResult)
{
    IntuneMAMAddIdentityResultSuccess,
    IntuneMAMAddIdentityResultFailed
};


@protocol IntuneMAMPolicyDelegate <NSObject>

@optional

// Called by the Intune SDK to inform the application an identity switch is required.
// The application must call the completion handler. IntuneMAMSwitchIdentityResultSuccess should
// be passed to the completion handler if the SDK is allowed to switch to the specified identity,
// otherwise IntuneMAMSwitchIdentityResultFailed should be passed in.
// The SDK will block the operation which required the identity
// switch until the application calls the completion handler. This method may also be
// called in response to a user clicking the 'cancel' button on the PIN or
// Authentication UI after an application resume.
// The completion handler can be called on any thread.
// The application does not have to call setUIPolicyIdentity in response to this call.
- (void) identitySwitchRequired:(NSString*_Nonnull)identity reason:(IntuneMAMIdentitySwitchReason)reason completionHandler:(void (^_Nonnull)(IntuneMAMSwitchIdentityResult))completionHandler;

// Called by the Intune SDK when the application should wipe data for the
// specified account user principal name (e.g. user@contoso.com).
// Returns TRUE if successful, FALSE if the account data could not be completely wiped.
- (BOOL) wipeDataForAccount:(NSString*_Nonnull)upn;

// Called by the Intune SDK when the application needs to restart
// because policy has been received for the first time, or if we're handling a mam-ca remediation
// and are restarting as a part of a SW because we need to remove an existing user.
// This method is called on a background thread.
// Returns TRUE if the host application will restart on its own.
// Returns FALSE if the host application wants the Intune SDK to handle the restart
- (BOOL) restartApplication;

// Called by the Intune SDK when the application needs to add an user account as the app has been
// automatically enrolled by the SDK. The application must call the completion handler passing in
// IntuneMAMAddIdentityResultSuccess if the app is able to add the identity or IntuneMAMAddIdentityResultFailed otherwise.
// The completion handler can be called on any thread.
- (void) addIdentity:(NSString*_Nonnull)identity completionHandler:(void (^_Nonnull)(IntuneMAMAddIdentityResult))completionHandler;

@end
