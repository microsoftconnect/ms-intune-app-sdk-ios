//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import "IntuneMAMLogger.h"
#import "IntuneMAMPolicy.h"
#import "IntuneMAMPolicyDelegate.h"
#import <UIKit/UIKit.h>

// Notification name for Intune application policy change notifications.
// Applications can register for notifications using the default NSNotificationCenter.
// The NSNotification passed to the observer will contain the IntuneMAMPolicyManager instance
// as the object.
__attribute__((visibility("default")))
extern NSString*_Nonnull const IntuneMAMPolicyDidChangeNotification;

// UserInfo dictionary constants.
__attribute__((visibility("default")))
extern NSString*_Nonnull const IntuneMAMPolicyDidChangeNotificationAccountId;

// Notification posted after the Intune SDK completes wiping the managed account.
__attribute__((visibility("default")))
extern NSString*_Nonnull const IntuneMAMWipeDidCompleteNotification;

// MAM policy source
typedef NS_ENUM(NSInteger, IntuneMAMPolicySource)
{
    IntuneMAMPolicySource_MDM = 0,      //  the policy is from the MDM channel
    IntuneMAMPolicySource_MAM = 1,      //  the policy is from the MAM channel
    IntuneMAMPolicySource_Other = 2,
};

// MAM web view policy
typedef NS_ENUM(NSInteger, IntuneMAMWebViewPolicy)
{
    IntuneMAMWebViewPolicyUnset = 0,            // the web view will be treated according to the TreatAllWebviewsAsUnmanaged flag
    IntuneMAMWebViewPolicyUnmanaged = 1,        // the web view will be treated as unmanaged
    IntuneMAMWebViewPolicyCurrentIdentity = 2,  // the web view will be treated as the current ui identity
};

__attribute__((visibility("default")))
@interface IntuneMAMPolicyManager : NSObject

+ (IntuneMAMPolicyManager*_Nonnull) instance;

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
- (void) setUIPolicyIdentity:(NSString*_Nullable)identity completionHandler:(void (^_Nullable)(IntuneMAMSwitchIdentityResult))completionHandler;
- (void) setUIPolicyIdentity:(NSString*_Nullable)identity forWindow:(UIWindow*_Nullable)window completionHandler:(void (^_Nullable)(IntuneMAMSwitchIdentityResult))completionHandler;
- (void) setUIPolicyAccountId:(NSString*_Nullable)accountId completionHandler:(void (^_Nullable)(IntuneMAMSwitchIdentityResult))completionHandler;
- (void) setUIPolicyAccountId:(NSString*_Nullable)accountId forWindow:(UIWindow*_Nullable)window completionHandler:(void (^_Nullable)(IntuneMAMSwitchIdentityResult))completionHandler;

// Returns the UI identity for the current key window.
- (NSString*_Nullable) getUIPolicyIdentity;

// Returns the UI AccountId (e.g. 3ec2c00f-b125-4519-acf0-302ac3761822) for the current key window.
- (NSString*_Nullable) getUIPolicyAccountId;

// Returns the UI identity for the specified window.
- (NSString*_Nullable) getUIPolicyIdentityForWindow:(UIWindow*_Nullable)window;

// Returns the UI AccountId (e.g. 3ec2c00f-b125-4519-acf0-302ac3761822) for the specified window.
- (NSString*_Nullable) getUIPolicyAccountIdForWindow:(UIWindow*_Nullable)window;

// setCurrentThreadIdentity sets the identity of the current thread which is used to determine what
// policy should be applied on the current thread. Unlike setting setUIPolicyIdentity, this method
// will not run the conditional launch policy checks for the user.
//
// The current thread identity overrides the process identity if set.
//
// The empty string may be passed in as the identity to represent 'no user' or an unknown personal account.
// If nil is passed in, the thread identity will fallback to the process identity.
- (void) setCurrentThreadIdentity:(NSString*_Nullable)identity  NS_SWIFT_UNAVAILABLE("Use the IntuneMAMSwiftContextManager.setIdentity(_ :forScope:) APIs instead.") __deprecated_msg("Use setCurrentThreadIdentity:forScope: instead.");

// setCurrentThreadAccountId sets the AccountId (e.g. 3ec2c00f-b125-4519-acf0-302ac3761822) of the current thread which is used to determine what
// policy should be applied on the current thread. Unlike setting setUIPolicyAccountId, this method
// will not run the conditional launch policy checks for the user.
//
// The current thread AccountId overrides the process AccountId if set.
//
// The empty string may be passed in as the accountId to represent 'no user' or an unknown personal account.
// If nil is passed in, the thread AccountId will fallback to the process AccountId.
- (void) setCurrentThreadAccountId:(NSString*_Nullable)accountId  NS_SWIFT_UNAVAILABLE("Use the IntuneMAMSwiftContextManager.setAccountId(_ :forScope:) APIs instead.") __deprecated_msg("Use setCurrentThreadAccountId:forScope: instead.");

// Similar to the setCurrentThreadIdentity:, setCurrentThreadIdentity:forScope: will set the current thread identity but only for the scope of the passed block
// It is preferable to use scoped thread identities to ensure that they are only set for a specified scope and will have a guaranteed removal.
- (void) setCurrentThreadIdentity:(NSString*_Nullable)identity forScope:(void(^_Nullable)(void))scope  NS_SWIFT_UNAVAILABLE("Use the IntuneMAMSwiftContextManager.setIdentity(_ :forScope:) APIs instead.");

// setCurrentThreadAccountId:forScope: will set the current thread AccountId (e.g. 3ec2c00f-b125-4519-acf0-302ac3761822) but only for the scope of the passed block
// It is preferable to use scoped thread identities to ensure that they are only set for a specified scope and will have a guaranteed removal.
- (void) setCurrentThreadAccountId:(NSString*_Nullable)accountId forScope:(void(^_Nullable)(void))scope  NS_SWIFT_UNAVAILABLE("Use the IntuneMAMSwiftContextManager.setAccountId(_ :forScope:) APIs instead.");

- (NSString*_Nullable) getCurrentThreadIdentity;

// Return current thread AccountId (e.g. 3ec2c00f-b125-4519-acf0-302ac3761822).
- (NSString*_Nullable) getCurrentThreadAccountId;

// setProcessIdentity sets the process wide identity.
- (void) setProcessIdentity:(NSString*_Nullable)identity;
- (NSString*_Nullable) getProcessIdentity;

// setProcessIdentity sets the process wide AccountId (e.g. 3ec2c00f-b125-4519-acf0-302ac3761822).
- (void) setProcessAccountId:(NSString*_Nullable)accountId;
- (NSString*_Nullable) getProcessAccountId;

// Returns the identity of the user which initiated the current activity.
// This method can be called within the openURL handler to retrieve the sender's identity.
- (NSString*_Nullable) getIdentityForCurrentActivity;

// Returns the AccountId (e.g. 3ec2c00f-b125-4519-acf0-302ac3761822) of the user which initiated the current activity.
// This method can be called within the openURL handler to retrieve the sender's AccountId.
- (NSString*_Nullable) getAccountIdForCurrentActivity;

// Returns TRUE if Intune management policy is applied or required for the application.
// Returns FALSE if no Intune management policy is applied and policy is not required.
- (BOOL) isManagementEnabled;

// Returns TRUE if the specified identity is managed.
- (BOOL) isIdentityManaged:(NSString*_Nullable)identity;

// Returns TRUE if the specified accountId (e.g. 3ec2c00f-b125-4519-acf0-302ac3761822) is managed.
- (BOOL) isAccountIdManaged:(NSString*_Nullable)accountId;

// Returns TRUE if the two identities are equal. This method performs a case insensitive compare
// as well as comparing the AAD object ids of the identities (if known) to determine if the identities
// are the same.
- (BOOL) isIdentity:(NSString*_Nullable)identity1 equalTo:(NSString*_Nullable)identity2;

// Returns an object that can be used to retrieve the MAM policy for the current thread identity.
- (_Nullable id  <IntuneMAMPolicy>) policy;

// Returns an object that can be used to retrieve the MAM policy for the specified identity.
- (_Nullable id<IntuneMAMPolicy>) policyForIdentity:(NSString*_Nullable)identity;

// Returns an object that can be used to retrieve the MAM policy for the specified AccountId (e.g. 3ec2c00f-b125-4519-acf0-302ac3761822).
- (_Nullable id<IntuneMAMPolicy>) policyForAccountId:(NSString*_Nullable)accountId;

// Returns an object that can be used to retrieve the MAM policy for the specified window.
- (_Nullable id<IntuneMAMPolicy>) policyForWindow:(UIWindow*_Nullable)window;

// Sets an IntuneMAMWebViewPolicyDelegate for the passed in WKWebView or SFSafariViewController.
// This delegate should be set for each WKWebView or SFSafariViewController being used to access
// arbitrary URLs or URLs that might access external data. See IntuneMAMPolicyDelegate.h for more
// information about this delegate and if it needs to be set.
- (void) setWebViewPolicyDelegate:(id<IntuneMAMWebViewPolicyDelegate>_Nullable)delegate forWebViewer:(id _Nonnull)webViewer;

// Sets an IntuneMAMWebViewPolicy value for the passed in UIView or UIViewController. This web
// view policy value will apply to any current or future child WKWebViews of the webViewer. A
// WKWebView can also be passed in directly as the webViewer. The passed in webViewPolicy will
// overwrite the TreatAllWebViewsAsUnmanaged flag for the passed in webViewer and its children.
- (void) setWebViewPolicy:(IntuneMAMWebViewPolicy)webViewPolicy forWebViewer:(id _Nonnull)webViewer;

// Returns the account name of the primary user in upn format (e.g. user@contoso.com).
// Should be called only by applications which don't support multiple managed accounts.
@property (readonly) NSString* _Nullable primaryUser;

// Returns the account name of the primary user in AccountId format (e.g. 3ec2c00f-b125-4519-acf0-302ac3761822).
// Should be called only by applications which don't support multiple managed accounts.
@property (readonly) NSString* _Nullable primaryAccountId;

// Returns an array of managed accounts in AccountId format (e.g. 3ec2c00f-b125-4519-acf0-302ac3761822).
@property (readonly) NSArray<NSString*>* _Nonnull managedAccountIds;

// The delegate property is used to notify the application of certain policy actions that
// it should perform. See IntuneMAMPolicyDelegate.h for more information.
// This property must be set by the time the application's UIApplicationDelegate
// application:willFinishLaunchingWithOptions method returns.
@property (nonatomic,strong, nullable) id<IntuneMAMPolicyDelegate> delegate;

// Logger used by the Intune MAM SDK.
@property (nonatomic,strong, nullable) id<IntuneMAMLogger> logger;

// Returns the method used to obtain the Intune MAM policy. Use this property for telemetry or logging purposes.
@property (nonatomic,readonly) IntuneMAMPolicySource mamPolicySource;

@end
