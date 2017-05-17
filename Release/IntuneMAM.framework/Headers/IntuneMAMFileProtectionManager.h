//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IntuneMAM/IntuneMAMFileProtectionInfo.h>


@interface IntuneMAMFileProtectionManager : NSObject

+ (IntuneMAMFileProtectionManager*) instance;

// Protects the specified path using the policy associated with the specified identity.
- (void) protect:(NSString*)path identity:(NSString*)identity;

// Returns the protection information for the specified path. Returns nil if the
// path does not exist or the path is not managed by the Intune MAM SDK.
- (id<IntuneMAMFileProtectionInfo>) protectionInfo:(NSString*)path;

@end
