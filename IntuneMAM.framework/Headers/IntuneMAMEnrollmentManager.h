//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IntuneMAM/IntuneMAMEnrollmentDelegate.h>

@interface IntuneMAMEnrollmentManager : NSObject

#pragma mark - Public APIs

/**
 *  This property should be to the delegate object created by the application.
 */
@property (nonatomic,weak) id<IntuneMAMEnrollmentDelegate> delegate;

/**
 *  Returns the instance of the IntuneMAMEnrollmentManager class
 *
 *  @return IntuneMAMEnrollmentManager shared instance
 */
+ (IntuneMAMEnrollmentManager*) instance;

/**
 *  Init is not available, please use instance:
 *
 *  @return nil
 */
- (id) init __attribute__((unavailable("Must use + (IntuneMAMEnrollmentManager*) instance")));

/**
 *  This method will add the account to the list of registered accounts.
 *  An enrollment request will immediately be started.  If the enrollment
 *  is not successful, the SDK will periodically re-try the enrollment every
 *  24 hours.  
 *  If the application has already registered an account using this API, and calls
 *  it again, the SDK will ignore the request and output a warning.
 *  Any SDK API that requires enrollment will not be valid until after
 *  enrollment succeeds, for example AppConfig policy is not delivered until 
 *  after an enrollment.  Use the IntuneMAMEnrollmentDelegate to determine
 *  if the SDK has successfully enrolled and received policy.
 *
 *  @param identity The UPN of the account to be registered with the SDK
 */
- (void)registerAndEnrollAccount:(NSString *)identity;

/**
 *  Creates an enrollment request which is started immediately.
 *  The user will be prompted to enter their credentials, 
 *  and we will attempt to enroll the user.
 *  Any SDK API that requires enrollment will not be valid until after
 *  enrollment succeeds, for example AppConfig policy is not delivered until 
 *  after an enrollment.  Use the IntuneMAMEnrollmentDelegate to determine
 *  if the SDK has successfully enrolled and received policy.
 
 *  @param identity The UPN of the account to be logged in and enrolled.
 */
- (void)loginAndEnrollAccount: (NSString *)identity;

/**
 *  This method will remove the provided account from the list of
 *  registered accounts.  Once removed, if the account has enrolled
 *  the application, the account will be un-enrolled.
 *
 *  @note In the case where an un-enroll is initiated, this method will block
 *  until the MAM token is acquired, then return.  This method must be called before 
 *  the user is removed from the application (so that required AAD tokens are not purged
 *  before this method is called).
 *
 *  @param identity The UPN of the account to be removed.
 *  @param doWipe   If YES, a selective wipe if the account is un-enrolled
 */
- (void)deRegisterAndUnenrollAccount:(NSString *)identity withWipe:(BOOL)doWipe;

/**
 *  Returns a list of UPNs of account currently registered with the SDK.
 *
 *  @return Array containing UPNs of registered accounts
 */
- (NSArray *)registeredAccounts;

/**
 *  Returns the UPN of the currently enrolled user.  Returns
 *  nil if the application is not currently enrolled.
 *
 *  @return UPN of the enrolled account
 */
- (NSString *)enrolledAccount;

@end
