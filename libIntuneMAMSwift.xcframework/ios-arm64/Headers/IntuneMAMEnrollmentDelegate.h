//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IntuneMAMEnrollmentStatus.h"

/**
 *  This is the interface for the concrete class to be instantiated and returned by the delegate when the
 *  Intune MAM sdk calls to get the user's enrollment token. See the getAccessTokenForUser:resource:completion:
 *  method below.
 */
__attribute__((visibility("default")))
@interface IntuneMAMEnrollmentToken : NSObject
@property (strong, atomic, nullable) NSString *   accessToken;   //  access token used by the Intune MAM SDK to get policy
@property (strong, atomic, nullable) NSString *   upn;                        //  user principal name
@property (strong, atomic, nullable) NSString *   oid;                        //  object ID for the user
@property (strong, atomic, nullable) NSString *   tenantId;                   //  GUID tenant identifier (optional)
@property (strong, atomic, nullable) NSString *   correlationId;              //  service correlation identifier (optional)
@property (strong, atomic, nullable) NSError  *   error;                      //  not used if the intuneMAMEnrollmentToken is returned; required otherwise
@end

/**
 *  This delegate will return status and debug information for operations 
 *  completed by the Intune MAM SDK. 
 */
__attribute__((visibility("default")))
@protocol IntuneMAMEnrollmentDelegate <NSObject>

#pragma mark - Delegate Methods

@optional

/**
 *  Called when an enrollment request operation is completed.
 *
 *  @param status status object containing status
 */
- (void)enrollmentRequestWithStatus:(IntuneMAMEnrollmentStatus *_Nonnull)status;

/**
 *  Called when a MAM policy request operation is completed.
 *
 *  @param status status object containing status
 */
- (void)policyRequestWithStatus:(IntuneMAMEnrollmentStatus *_Nonnull)status;

/**
 *  Called when a un-enroll request operation is completed.
 *
 *  @Note: when a user is un-enrolled, the user is also de-registered with the SDK
 *
 *  @param status status object containing status
 */
- (void)unenrollRequestWithStatus:(IntuneMAMEnrollmentStatus *_Nonnull)status;

/**
 *  Called when a enrollment or policy refresh requires an access token to the MAM
 *      service
 *
 *
 *  @Note: the call should not block
 *  @Note: the app can require the user to authenticate if needed
 *  @Note: if this method is not implemented, the Intune SDK uses the Auth Framework directly to
 *          get the access token
 *
 *  @param oid      this is the user for whom we require an access token
 *  @param resource this is the MAM service resource that we require access to
 */
- (void) getAccessTokenForAccountId:(NSString *_Nonnull)oid resource:(NSString *_Nonnull)resource completion:(void(^_Nonnull)(IntuneMAMEnrollmentToken *_Nonnull))completion;

@end
