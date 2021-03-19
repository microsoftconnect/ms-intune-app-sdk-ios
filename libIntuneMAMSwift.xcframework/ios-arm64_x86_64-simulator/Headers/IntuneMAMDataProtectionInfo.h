//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

__attribute__((visibility("default")))
@protocol IntuneMAMDataProtectionInfo <NSObject>

@required

// The data's owner.
@property (readonly,nullable) NSString* identity;

@end
