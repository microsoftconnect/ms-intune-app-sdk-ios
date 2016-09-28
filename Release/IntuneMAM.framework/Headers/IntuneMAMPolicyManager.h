//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IntuneMAMPolicyDelegate.h"
#import "IntuneMAMPolicy.h"
#import "IntuneMAMAsyncResult.h"
#import "IntuneMAMLogger.h"
#import "IntuneMAMDefs.h"

// Notification name for Intune application policy change notifications.
// Applications can register for notifications using the default NSNotificationCenter.
// The NSNotification passed to the observer will contain the IntuneMAMPolicyManager instance
// as the object and userInfo will be nil.
extern NSString* const IntuneMAMPolicyDidChangeNotification;


@interface IntuneMAMPolicyManager : NSObject

+ (IntuneMAMPolicyManager*) instance;

// setUIPolicyIdentity attempts to switch the UI thread identity to the specified user.
// If the specified user is managed, the SDK will run the conditional launch checks and
// depending on policy may check device compliance, prompt the user for PIN, prompt the
// user for authentication, etc.
//
// The switch identity call may fail or may be canceled by the user. The application should
// delay the operation that requires the identity switch until the result has been returned
// via the completion handler. The completion handler is called on the main thread.
// The possible result codes are:
//
// IntuneMAMSwitchIdentityResultSuccess - The identity change was successful.
// IntuneMAMSwitchIdentityResultCanceled - The identity change was canceled by the user.
// IntuneMAMSwitchIdentityResultNotAllowed - Switching identities is not currently allowed by the SDK.
//      This will be returned if the identity is different from the enrolled user but is from
//      the same organization. Only a single managed identity is allowed in this release.
//      This will also be returned if a thread identity is set on the main thread that does not
//      match the identity passed into this method. If the thread identity on the main thread
//      is different, it should be cleared before calling this method.
// IntuneMAMSwitchIdentityResultFailed - an Unknown error occurred.
//
// This call will not apply file policy on the main thread. To do this, setCurrentThreadIdentity
// must also be called on the main thread.
//
// The empty string may be passed in as the identity to represent 'no user' or an unknown personal account.
// If nil is passed in, the UI identity will fallback to the process identity.
- (void) setUIPolicyIdentity:(NSString*)identity completionHandler:(void (^)(IntuneMAMSwitchIdentityResult))completionHandler;
- (NSString*) getUIPolicyIdentity;

// setCurrentThreadIdentity sets the identity of the current thread which is used to determine what
// policy should be applied on the current thread. Unlike setting setUIPolicyIdentity, this method
// will not run the conditional launch policy checks for the user.
//
// The current thread identity overrides the process identity if set.
//
// The empty string may be passed in as the identity to represent 'no user' or an unknown personal account.
// If nil is passed in, the thread identity will fallback to the process identity.
- (void) setCurrentThreadIdentity:(NSString*)identity;
- (NSString*) getCurrentThreadIdentity;

// setProcessIdentity sets the process wide identity.
- (void) setProcessIdentity:(NSString*)identity;
- (NSString*) getProcessIdentity;

// Returns the identity of the user which initiated the current activity.
// This method can be called within the openURL handler to retrieve the sender's identity.
- (NSString*) getIdentityForCurrentActivity;

// Returns TRUE if the specified identity is managed.
- (BOOL) isIdentityManaged:(NSString*)identity;


// Returns an object that can be used to retrieve the MAM policy for the current thread identity.
- (id<IntuneMAMPolicy>) policy;

// Returns an object that can be used to retrieve the MAM policy for the specified identity.
- (id<IntuneMAMPolicy>) policyForIdentity:(NSString*)identity;


// Returns the account name of the primary user in upn format (e.g. user@contoso.com).
@property (readonly) NSString* primaryUser;

// The delegate property is used to notify the application of certain policy actions that
// it should perform. See IntuneMDMPolicyDelegate.h for more information.
// This property must be set by the time the application's UIApplicationDelegate
// application:willFinishLaunchingWithOptions method returns.
@property (nonatomic,strong) id<IntuneMAMPolicyDelegate> delegate;

// Logger used by the Intune MAM SDK.
@property (nonatomic,strong) id<IntuneMAMLogger> logger;

// Indicate if telemetry is opted-in or not.
@property (nonatomic) BOOL telemetryEnabled;

// Specifies which AAD authority URI the SDK should use. This property should be set
// if the application dynamically determines the AAD authority URI. If the authority
// URI is static, the ADALAuthority value under the IntuneMAMSettings dictionary should
// be used instead. This value is persisted across application launches.
@property (nonatomic,strong) NSString* aadAuthorityUriOverride;

// Uploads Intune logs and diagnostic information into Sara
-(void) sendDiagnosticInformation:(NSString*) clientID withSessionID:(NSString*) sessionID completionHandler:(void (^)(BOOL))completionHandler;

// Returns a dictionary of diagnostic information
-(NSDictionary*) getDiagnosticInformation;

@end


// Deprecated interfaces

// Switch identity result codes.
extern id const IntuneMAMSwitchIdentitySuccess;
extern id const IntuneMAMSwitchIdentityCanceled;
extern id const IntuneMAMSwitchIdentityNotAllowed;
extern id const IntuneMAMSwitchIdentityFailed;

// Add identity result codes
extern id const IntuneMAMAddIdentitySuccess;
extern id const IntuneMAMAddIdentityFailed;

@interface IntuneMAMPolicyManager (IntuneMAMPolicyManagerDeprecated)
- (void) setUIPolicyIdentity:(NSString*)identity withAsyncResult:(id<IntuneMAMAsyncResult>)result __attribute__((deprecated("Please use setUIPolicyIdentity:completionHandler:")));
@end

