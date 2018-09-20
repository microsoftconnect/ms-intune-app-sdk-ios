//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, IntuneMAMSaveLocation)
{
    IntuneMAMSaveLocationOther = 0,
    IntuneMAMSaveLocationOneDriveForBusiness = 1<<0,
    IntuneMAMSaveLocationSharePoint = 1<<1,
    IntuneMAMSaveLocationBox = 1<<2,
    IntuneMAMSaveLocationDropbox = 1<<3,
    IntuneMAMSaveLocationGoogleDrive = 1<<4,
    IntuneMAMSaveLocationLocalDrive = 1<<5,

};

@protocol IntuneMAMPolicy <NSObject>

@required

// TRUE if the management policy requires the user to enter a PIN.
// The SDK will automatically handle displaying the PIN UI. If the application
// has its own PIN support and this method returns true, the application should
// not show its own PIN UI.
@property (readonly) BOOL isPINRequired;


// TRUE if the management policy allows applications to save managed files to the account accountName
// in the given location. Applications should check this policy and if FALSE should disable any UI
// which allows users to save managed documents to this account in this location.
// If the accountName for the location is unknown, set this argument to nil. 
- (BOOL) isSaveToAllowedForLocation: (IntuneMAMSaveLocation) location withAccountName: (NSString*_Nullable) accountName;

// FALSE if the management policy blocks application opening/querying the specified URL.
// Returns TRUE otherwise, regardless of whether the scheme is listed in the application's
// LSApplicationQueriesSchemes.  Applications can check this policy to customize their UI.
// Policy enforcement will be entirely handled by the SDK.
- (BOOL) isURLAllowed: (NSURL*_Nonnull) url;

// FALSE if the management policy blocks the application from opening the specified URL with the
// UIApplicationOpenURLOptionUniversalLinksOnly option set to @YES. Returns TRUE otherwise.
// Applications can check this policy to customize their UI. Policy enforcement will be entirely handled
// by the SDK.
- (BOOL) isUniversalLinkAllowed: (NSURL*_Nonnull) url;

// FALSE if the management policy blocks the specified document picker mode.  Returns TRUE
// otherwise, regardless of whether there are managed document picker extensions in the
// UIDocumentPickerViewController that can accept the managed file. Applications can check
// this policy to customize their UI. Policy enforcement will be entirely handled by the SDK.
- (BOOL) isDocumentPickerAllowed: (UIDocumentPickerMode) mode;

// TRUE if the management policy requires the Intune Managed Browser to handle HTTP/HTTPS
// requests. Applications can check this policy to customize their UI. Policy enforcement
// will be entirely handled by the SDK.
@property (readonly) BOOL isManagedBrowserRequired;

// TRUE if the management policy allows applications to sync corporate contact data to
// the native app.  Multi-Identitity applications should check this policy and if FALSE should not sync
// corporate contacts to the native app.  For single identity applications, policy enforcement will be
// entirely handled by the SDK.
@property (readonly) BOOL isContactSyncAllowed;

// TRUE if the management policy allows applications to index coporate data for
// Core Spotlight.  Multi-Identity applications should check this policy and if FALSE should set
// eligibleForPublicIndexing and eligibleForSearch to FALSE for corporate NSUserActivity objects
// and disallow indexing of corporate data through Core Spotlight.  For single identity applications,
// policy enforcement will be entirely handled by the SDK.
@property (readonly) BOOL isSpotlightIndexingAllowed;

// FALSE if the management policy blocks sharing via the UIActivityViewController/
// UIDocumentInteractionViewController.  Returns TRUE otherwise, regardless of whether there are
// managed applications or share extensions available to share the data with.  Applications can check
// this policy to customize their UI. Policy enforcement will be entirely handled by the SDK.
@property (readonly) BOOL isAppSharingAllowed;

// TRUE if management policy requires File Provider extensions to encrypt files. Applications
// should check for this policy in their File provider extension if they are supporting iOS11 or higher
// File Provider APIs. Policy enforcement will not be handled by the SDK. Application will explicitly
// need to invoke encryptFile:forIdentity API in IntuneMAMFileProtectionManager for each file exposed by
// the File Provider.
@property (readonly) BOOL shouldFileProviderEncryptFiles;

@end
