//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

// Intune MAM logging interface.
@protocol IntuneMAMLogger<NSObject>

typedef enum IntuneMAMLogLevel
{
    IntuneMAMLogLevelVerbose,
    IntuneMAMLogLevelInfo,
    IntuneMAMLogLevelWarning,
    IntuneMAMLogLevelError
} IntuneMAMLogLevel;

@required

// Message with IntuneMAMLogLevelVerbose may contain PII (Personally Identifiable Information) data.
// Message with IntuneMAMLogLevelInfo/IntuneMAMLogLevelWarning/IntuneMAMLogLevelError is guarenteed
// to contain no PII data.
- (void) log:(NSString*)message level:(IntuneMAMLogLevel)level;

@end
