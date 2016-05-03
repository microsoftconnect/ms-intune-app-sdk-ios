//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IntuneMAMAsyncResult.h"

// MAM Service Enrollment result codes
extern id const IntuneMAMServiceEnrollmentSuccess;
extern id const IntuneMAMServiceEnrollmentAuthorizationNeeded;
extern id const IntuneMAMServiceEnrollmentFailed;
extern id const IntuneMAMServiceEnrolledMDM;
extern id const IntuneMAMServiceNotLicensed;
extern id const IntuneMAMServiceTooManyRequests;

// MAM Service UnEnrollment result codes
extern id const IntuneMAMServiceUnEnrollmentSuccess;
extern id const IntuneMAMServiceUnEnrollmentFailed;

// MAM Service results codes that can be returned for enroll or un-enroll
extern id const IntuneMAMServiceDisabled;
extern id const IntuneMAMServiceRequestOngoing;
extern id const IntuneMAMServiceWrongUser;

@interface IntuneMAMEnrollmentManager : NSObject

- (id) init __attribute__((unavailable("Must use + (IntuneMAMEnrollmentManager*) instance")));

/**
 *  Returns the instance of the IntuneMAMEnrollmentManager class
 *
 *  @return IntuneMAMEnrollmentManager shared instance
 */
+ (IntuneMAMEnrollmentManager*) instance;

/**
 *  enrollApplication attempts to enroll the application in the Intune MAM Service using
 *  the identity provided.  The result of the enrollment operation is returned on the main
 *  thread.  If enrollment succeeds, the application will check in with the MAM service for updated policy
 *  at an interval provided in the by the user's IT Department.  If the enrollment fails, the host
 *  application is expected to block access to the application.
 *
 *  @param identity The UPN of the user to be enrolled
 *  @param result   The Async Result that will be called back with a result code
 *
 *  Possible return codes sent to host application:
 * - IntuneMAMServiceEnrollmentSuccess - Enrollment was successful for that user (or that user
 *   is already enrolled).
 * - IntuneMAMServiceEnrollmentAuthorizationNeeded - The SDK was unable to access the required
 *   refresh token.  The application should prompt for credentials.
 * - IntuneMAMServiceEnrollmentFailed - Failed to enroll the provided, MAM licensed identity for an unknown reason.
 *   The application should log the user out of the application because policies cannot be retrieved.
 * - IntuneMAMServiceEnrolledMDM - The provided, MAM licensed identity cannot be enrolled because the 
 *   device is already MDM enrolled and the provided identity does not match the MDM enrolled identity.
 *   The application must log out the user.
 * - IntuneMAMServiceWrongUser - The provided, MAM licensed identity cannot be enrolled because the user
 *   is not the primary user.
 * - IntuneMAMServiceRequestOngoing - Only one request can occur at a time.
 *   This is returned when another request is currently being processed. The caller should retry 
 *   the enrollment request.
 * - IntuneMAMServiceNotLicensed - The provided identity is not licensed for MAM.  The application should
 *   allow the user to continue.
 * - IntuneMAMServiceTooManyRequests - The application has made too many requests in the past 24 hours.  
 *   The application should try again in 24 hours.
 * - IntuneMAMServiceDisabled - The application has disabled MAM Service functionality.  As a result
 *   all requests to the API will return with this result.
 */
- (void) enrollApplication:(NSString *)identity withAsyncResult:(id<IntuneMAMAsyncResult>)result;

/**
 *  unEnrollApplication attempts to remove all MAM policies and leave the provided identity
 *  in an un-managed state.  If successful, the user will not have any MAM policies and
 *  no requests will be made to the service for policy updates.  The result is returned
 *  on the main thread.
 *
 *  @Warning A selective wipe will happen as part of unenrollment
 *
 *  @param identity The UPN of the user to be unenrolled
 *  @param result   The Async Result that will be called back with a result code
 *
 *  Possible return codes sent to host application:
 * - IntuneMAMServiceUnEnrollmentSuccess - Unenrollment was successful for that user (or that user
 *   was never enrolled).
 * - IntuneMAMServiceUnEnrollmentFailed - The SDK was unable to complete the un-enrollment because of an 
 *   unknown error.
 * - IntuneMAMServiceWrongUser - The provided, MAM licensed identity cannot be un-enrolled because the user
 *   is not the enrolled user.
 * - IntuneMAMServiceDisabled - The application has disabled MAM Service functionality.  As a result
 *   all requests to the API will return with this result.
 */
- (void) unEnrollApplication:(NSString *)identity withAsyncResult:(id<IntuneMAMAsyncResult>)result;

/**
 *  This method will switch the device's primary user to the provided UPN.  If the current application is 
 *  enrolled in the MAM Service under a previous user, it will be un-enrolled.
 *
 *  @Warning Calling this method will cause the current AND any other application enrolled by the previous
 *           user to be un-enrolled and selectively wiped!
 *
 *  @param identity The UPN of the new primary user of the device
 *  @param result   The Async Result that will be called back with the result code
 *
 *  Possible return codes sent to host application:
 * - IntuneMAMServiceUnEnrollmentSuccess - Unenrollment and primary user switch was successful for that 
 *   user (or that user was never enrolled).  This will also be returned even if the app was not originally
 *   enrolled in the MAM Service.
 * - IntuneMAMServiceUnEnrollmentFailed - The SDK was unable to complete the un-enrollment and/or primary
 *   user switch.  This should not occur and represents a bug in the SDK.
 * - IntuneMAMServiceDisabled - The application has disabled MAM Service functionality.  As a result
 *   all requests to the API will return with this result.

 */
- (void)unEnrollApplicationAndSwitchPrimaryUserTo:(NSString *)identity withAsyncResult:(id<IntuneMAMAsyncResult>)result;

/**
 *  Returns the user that has first enrolled a MAM application and
 *  is now the device's primary user.  Only this user can enroll other
 *  apps on the device.  All other MAM licensed users that attempt to enroll 
 *  will receive the IntuneMAMServiceWrongUser error code.  The method will
 *  return nil if no user has yet enrolled an application in the MAM Service.
 *
 *  @return UPN of the device's primary user
 */
- (NSString *)devicePrimaryUser;

@end
