//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol IntuneMAMDataProtectionInfo <NSObject>

@required

// The data's owner.
@property (readonly) NSString* identity;

@end
