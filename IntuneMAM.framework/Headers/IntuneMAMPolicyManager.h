//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <IntuneMAM/IntuneMAMLogger.h>
#import <IntuneMAM/IntuneMAMPolicy.h>
#import <IntuneMAM/IntuneMAMPolicyDelegate.h>

// Notification name for Intune application policy change notifications.
// Applications can register for notifications using the default NSNotificationCenter.
// The NSNotification passed to the observer will contain the IntuneMAMPolicyManager instance
// as the object and userInfo will be nil.
extern NSString*_Nonnull const IntuneMAMPolicyDidChangeNotification;

// MAM policy source
typedef NS_ENUM(NSInteger, IntuneMAMPolicySource)
{
    IntuneMAMPolicySource_MDM = 0,      //  the policy is from the MDM channel
    IntuneMAMPolicySource_MAM = 1,      //  the policy is from the MAM channel
    IntuneMAMPolicySource_Other = 2,
};

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

// Returns the UI identity for the current key window.
- (NSString*_Nullable) getUIPolicyIdentity;

// Returns the UI identity for the specified window.
- (NSString*_Nullable) getUIPolicyIdentityForWindow:(UIWindow*_Nullable)window;

// setCurrentThreadIdentity sets the identity of the current thread which is used to determine what
// policy should be applied on the current thread. Unlike setting setUIPolicyIdentity, this method
// will not run the conditional launch policy checks for the user.
//
// The current thread identity overrides the process identity if set.
//
// The empty string may be passed in as the identity to represent 'no user' or an unknown personal account.
// If nil is passed in, the thread identity will fallback to the process identity.
- (void) setCurrentThreadIdentity:(NSString*_Nullable)identity;
- (NSString*_Nullable) getCurrentThreadIdentity;

// setProcessIdentity sets the process wide identity.
- (void) setProcessIdentity:(NSString*_Nullable)identity;
- (NSString*_Nullable) getProcessIdentity;

// Returns the identity of the user which initiated the current activity.
// This method can be called within the openURL handler to retrieve the sender's identity.
- (NSString*_Nullable) getIdentityForCurrentActivity;

// Returns TRUE if Intune management policy is applied or required for the application.
// Returns FALSE if no Intune management policy is applied and policy is not required.
- (BOOL) isManagementEnabled;

// Returns TRUE if the specified identity is managed.
- (BOOL) isIdentityManaged:(NSString*_Nullable)identity;

// Returns TRUE if the two identities are equal. This method performs a case insensitive compare
// as well as comparing the AAD object ids of the identities (if known) to determine if the identities
// are the same.
- (BOOL) isIdentity:(NSString*_Nullable)identity1 equalTo:(NSString*_Nullable)identity2;

// Returns an object that can be used to retrieve the MAM policy for the current thread identity.
- (_Nullable id  <IntuneMAMPolicy>) policy;

// Returns an object that can be used to retrieve the MAM policy for the specified identity.
- (_Nullable id<IntuneMAMPolicy>) policyForIdentity:(NSString*_Nullable)identity;

// Returns an object that can be used to retrieve the MAM policy for the specified window.
- (_Nullable id<IntuneMAMPolicy>) policyForWindow:(UIWindow*_Nullable)window;

// Returns the account name of the primary user in upn format (e.g. user@contoso.com).
@property (readonly) NSString* _Nullable primaryUser;

// The delegate property is used to notify the application of certain policy actions that
// it should perform. See IntuneMDMPolicyDelegate.h for more information.
// This property must be set by the time the application's UIApplicationDelegate
// application:willFinishLaunchingWithOptions method returns.
@property (nonatomic,strong, nullable) id<IntuneMAMPolicyDelegate> delegate;

// Logger used by the Intune MAM SDK.
@property (nonatomic,strong, nullable) id<IntuneMAMLogger> logger;

// Returns the method used to obtain the Intune MAM policy. Use this property for telemetry or logging purposes.
@property (nonatomic,readonly) IntuneMAMPolicySource mamPolicySource;

#pragma mark - Deprecated APIs

- (NSArray*_Nullable) aadAuthorityUrisForIdentity:(NSString*_Nullable)identity __attribute__((deprecated("This method is deprecated and will be removed in a future release. Use [IntuneMAMSettings aadAuthorityUrisForIdentity:identity] instead")));

@property (nonatomic) BOOL telemetryEnabled __attribute__((deprecated("This property is deprecated and will be removed in a future release. Use [IntuneMAMSettings telemetryEnabled] instead")));

@property (nonatomic,strong,nullable) NSString* aadAuthorityUriOverride __attribute__((deprecated("This property is deprecated and will be removed in a future release. Use [IntuneMAMSettings aadAuthorityUriOverride] instead")));

@property (nonatomic,strong,nullable) NSString* aadRedirectUriOverride __attribute__((deprecated("This property is deprecated and will be removed in a future release. Use [IntuneMAMSettings aadRedirectUriOveride] instead")));

@property (nonatomic,strong,nullable) NSString* aadClientIdOverride __attribute__((deprecated("This property is deprecated and will be removed in a future release. Use [IntuneMAMSettings aadClientIdOverride] instead")));

-(NSDictionary*_Nullable) getDiagnosticInformation __attribute__((deprecated("This method is deprecated and will be removed in a future release. Use [IntuneMAMDiagnosticConsole getDiagnosticInformation] instead")));

- (NSArray*_Nullable) getIntuneLogPaths __attribute__((deprecated("This method is deprecated and will be removed in a future release. Use [IntuneMAMDiagnosticConsole getIntuneLogPaths] instead")));

@end
