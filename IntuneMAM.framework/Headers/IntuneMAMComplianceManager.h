//
//  Copyright © Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, IntuneMAMComplianceStatus)
{
    IntuneMAMComplianceCompliant                = 0, // The user is compliant.
    IntuneMAMComplianceNotCompliant             = 1, // The user has been marked as non-compliant; the app should display the supplied localized string.
    IntuneMAMComplianceServiceFailure           = 2, // There was an error retrieving compliance data from the Intune Service; the app should try again later.
    IntuneMAMComplianceNetworkFailure           = 3, // There was an error connecting to the Intune Service; the app should try again when the network health is restored.
    IntuneMAMComplianceInteractionRequired      = 4, // The SDK encountered a scenario that requires user interaction, the app should call again with silent:NO.
    IntuneMAMComplianceUserCancelled            = 5  // The user has canceled the remediation attmempt.
};

/**
 *  This delegate will return compliance information requested by the app
 */
@protocol IntuneMAMComplianceDelegate <NSObject>

/**
 * This method is called when the Intune SDK has completed compliance remediation for an identity.
 * If the identity has not been added to the app and is compliant, it should be added at this time.
 * All values of IntuneMAMComplianceStatus will populate the error parameter with a localized error string.
 * Please note that delegate methods are not guarenteed to be called on the Main thread.
 *
 * @param identity The UPN of the identity for which compliance remediation was requested
 * @param status The compliance status of identity
 * @param error A localized string describing the error encountered if the identity is not compliant.
 */
- (void) identity:(NSString*_Nonnull) identity hasComplianceStatus:(IntuneMAMComplianceStatus) status withErrorMessage:(NSString*_Nonnull) errMsg andErrorTitle:(NSString*_Nonnull) errTitle;

@end

@interface IntuneMAMComplianceManager : NSObject

/**
 *  This property should be set to the delegate object created by the application.
 */
@property (nonatomic,weak,nullable) id<IntuneMAMComplianceDelegate> delegate;

+ (IntuneMAMComplianceManager*_Nonnull) instance;

/**
 * When an application requests a resource token from AAD, if it receives an error response indicating non-compliance,
 * the app must initiate Intune APP enrollment via remediateComplianceForIdentity:silent:
 *
 * Compliance status is returned via the delegate method identity:hasComplianceStatus:withErrorMessage:andErrorTitle:
 * The app should wait until this delegate method is called to retry the token acquisition
 *
 * @warning If the identity given has not already been enrolled into Intune, this method can cause an application restart.
 * In this case, the Intune SDK will take UI control at next application launch and call the delegate method identity:hasComplianceStatus:withErrorString: when finished
 * If the app knows this is a first time login for identity, it's recomended to set silent to NO as this will likely cause a restart
 *
 * @param identity The UPN of the identity sending the request
 * @param silent A bool indicating whether or not the Intune SDK will take UI control for the duration of the this method
 */
- (void) remediateComplianceForIdentity:(NSString*_Nonnull) identity silent:(BOOL) silent;

@end

