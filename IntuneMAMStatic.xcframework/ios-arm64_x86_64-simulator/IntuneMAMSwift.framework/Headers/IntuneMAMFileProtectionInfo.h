//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

__attribute__((visibility("default")))
@protocol IntuneMAMFileProtectionInfo <NSObject>

@required

// The UPN of file's owner (e.g. user@contoso.com)
@property (readonly,nullable) NSString* identity;
// The AccountId of the file's owner (e.g. 3ec2c00f-b125-4519-acf0-302ac3761822).
@property (readonly,nullable) NSString* accountId;

@end
