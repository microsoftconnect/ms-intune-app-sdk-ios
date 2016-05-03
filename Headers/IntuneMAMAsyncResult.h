//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

// IntuneMAMAsyncResult protocol defines an interface that is used to return a value from
// a function asynchronously. Classes that implement this protocol will typically implement
// a setValue method to notify the thread interested in the result that the operation
// has completed and the result is available.
@protocol IntuneMAMAsyncResult <NSObject>

@required
@property (atomic,strong) id value;

@end


// IntuneMAMAsyncResultCallback is an implementation of the IntuneMAMAsyncResult
// protocol which calls a function block when the result is set on the object.
@interface IntuneMAMAsyncResultCallback : NSObject<IntuneMAMAsyncResult>

- (id) initWithCallback:(void (^)(id<IntuneMAMAsyncResult>))callback;

@property (atomic,strong) id value;
@property (atomic,strong) void (^callback)(id<IntuneMAMAsyncResult>);

@end
