//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol IntuneMAMPolicy <NSObject>

@required

// TRUE if the management policy requires the user to enter a PIN.
// The SDK will automatically handle displaying the PIN UI. If the application
// has its own PIN support and this method returns true, the application should
// not show its own PIN UI.
@property (readonly) BOOL isPINRequired;

// TRUE if the management policy allows applications to save files to non-corporated
// locations. Applications should check this policy and if FALSE should disable any UI which
// allows users to save documents to personal account locations.
@property (readonly) BOOL isSaveToPersonalAllowed;

// TRUE if the management policy requires the Intune Managed Browser to handle HTTP/HTTPS
// requests. Applications can check this policy to customize their UI. Policy enforcement
// will be entirely handled by the SDK.
@property (readonly) BOOL isManagedBrowserRequired;

@end
