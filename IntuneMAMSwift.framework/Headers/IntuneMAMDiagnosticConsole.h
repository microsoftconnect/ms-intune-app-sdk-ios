//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IntuneMAMDiagnosticConsole : NSObject

//Immediately displays the Intune Diagnostic Console
+ (void) displayDiagnosticConsole;

// Returns a dictionary of diagnostic information
+ (NSDictionary*_Nullable) getDiagnosticInformation;

// Returns an array containing the string paths of the Intune SDK log files
// including the standard log file and the diagnostic log file.
// These files can then be uploaded to a back-end of the application's choosing.
+ (NSArray<NSString*>*_Nullable) getIntuneLogPaths;

#pragma mark - Deprecated API
// Immediately displays the Intune Diagnostic Console. Pass in "YES"
// if you want the dark mode UI
+ (void) displayDiagnosticConsoleInDarkMode:(BOOL)isDarkMode __attribute__((deprecated("This property is deprecated and will be removed in a future release. Use [IntuneMAMDiagnosticConsole displayDiagnosticConsole] instead. To customize the color scheme of the diagnostic console and other UI components of the Intune MAM SDK, use the backgroundColor, foregroundColor, and accentColor properties of the IntuneMAMSettings class.")));

@end
