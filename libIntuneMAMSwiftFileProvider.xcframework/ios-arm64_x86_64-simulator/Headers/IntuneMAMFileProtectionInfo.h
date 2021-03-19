//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

__attribute__((visibility("default")))
@protocol IntuneMAMFileProtectionInfo <NSObject>

@required

// The file's owner.
@property (readonly,nullable) NSString* identity;

@end
