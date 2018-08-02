//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IntuneMAMDataProtectionInfo.h"

// Notification name for Intune data protection level change notifications.
// Applications should re-protect data for the managed user after this
// notification is received.
// The NSNotification passed to the observer will contain the
// IntuneMAMDataProtectionManager instance as the object and userInfo will be nil.
extern NSString*_Nonnull const IntuneMAMDataProtectionDidChangeNotification;

@interface IntuneMAMDataProtectionManager : NSObject

+ (IntuneMAMDataProtectionManager*_Nonnull) instance;

// Protects the buffer using the policy associated with the specified identity.
// Returns nil if an error occurs.
- (NSData*_Nullable) protect:(NSData*_Nonnull)data identity:(NSString*_Nonnull)identity;

// Protects the string using the policy associated with the specified identity.
// Returns a base64 encoded encrypted buffer.
// Returns nil if an error occurs.
- (NSString*_Nullable) protectString:(NSString*_Nonnull)string identity:(NSString*_Nonnull)identity;

// Returns unprotected data.
// If the specified data was not returned by the protect call, it will be returned unchanged.
// Returns nil if an error occurs.
- (NSData*_Nullable) unprotect:(NSData*_Nonnull)data;

// Returns unprotected string.
// If the specified string was not returned by the protectString call, it will be returned unchanged.
// Returns nil if an error occurs.
- (NSString*_Nullable) unprotectString:(NSString*_Nonnull)string;

// Returns the protection information for the specified buffer.
// Returns nil if the data is not protected by the Intune MAM SDK.
- (id<IntuneMAMDataProtectionInfo>_Nullable) protectionInfo:(NSData*_Nonnull)data;

// Returns the protection information for the specified string.
// Returns nil if the data is not protected by the Intune MAM SDK.
- (id<IntuneMAMDataProtectionInfo>_Nullable) protectionInfoForString:(NSString*_Nonnull)string;

#if TARGET_OS_IPHONE
// Returns the protection information for the specified item provider.
// Share extensions can call this method to retreive the item's owner.
// The item must be loaded by calling loadItemForTypeIdentifier prior to calling this method.
// This method can be called from the completion handler passed to the loadItemForTypeIdentifier call.
// Returns nil if the item provider is not protected by the Intune MAM SDK.
- (id<IntuneMAMDataProtectionInfo>_Nullable) protectionInfoForItemProvider:(NSItemProvider*_Nonnull)itemProvider;
#endif

@end
