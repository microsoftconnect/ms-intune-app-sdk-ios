//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IntuneMAMEnrollmentStatus.h"

/**
 *  This delegate will return status and debug information for operations 
 *  completed by the Intune MAM SDK.  These are provided for the developer
 *  for debugging purposes only.  Note that specific status codes and debug
 *  messages may change, so no application business logic should be based off
 *  this information.
 */
@protocol IntuneMAMEnrollmentDelegate <NSObject>

#pragma mark - Delegate Methods

@optional

/**
 *  Called when an enrollment request operation is completed.
 *
 *  @param status status object containing debug information
 */
- (void)enrollmentRequestWithStatus:(IntuneMAMEnrollmentStatus *)status;

/**
 *  Called when a MAM policy request operation is completed.
 *
 *  @param status status object containing debug information
 */
- (void)policyRequestWithStatus:(IntuneMAMEnrollmentStatus *)status;

/**
 *  Called when a un-enroll request operation is completed.
 *
 *  @Note: when a user is un-enrolled, the user is also de-registered with the SDK
 *
 *  @param status status object containing debug information
 */
- (void)unenrollRequestWithStatus:(IntuneMAMEnrollmentStatus *)status;

@end
