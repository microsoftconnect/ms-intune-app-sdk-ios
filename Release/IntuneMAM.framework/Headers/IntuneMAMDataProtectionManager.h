//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IntuneMAMDataProtectionInfo.h"

@interface IntuneMAMDataProtectionManager : NSObject

+ (IntuneMAMDataProtectionManager*) instance;

// Protects the buffer using the policy associated with the specified identity.
// Returns nil if an error occurs.
- (NSData*) protect:(NSData*)data identity:(NSString*)identity;

// Returns unprotected data.
// If the specified data was not returned by the protect call, it will be returned unchanged.
// Returns nil if an error occurs.
- (NSData*) unprotect:(NSData*)data;

// Returns the protection information for the specified buffer.
// Returns nil if the data is not protected by the Intune MAM SDK.
- (id<IntuneMAMDataProtectionInfo>) protectionInfo:(NSData*)data;

// Returns the protection information for the specified item provider.
// Share extensions can call this method to retreive the item's owner.
// The item must be loaded by calling loadItemForTypeIdentifier prior to calling this method.
// This method can be called from the completion handler passed to the loadItemForTypeIdentifier call.
// Returns nil if the item provider is not protected by the Intune MAM SDK.
- (id<IntuneMAMDataProtectionInfo>) protectionInfoForItemProvider:(NSItemProvider*)itemProvider;

@end
