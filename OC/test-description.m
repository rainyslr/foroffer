#include <Foundation/Foundation.h>

@interface NSNull(Mytype)
- (NSString*) getPointer;
- (NSString*) description;
@end

@implementation NSNull(Mytype)
- (NSString*) getPointer {
	return [NSString stringWithFormat:@"%p", self];
}

- (NSString*) description {
	return [NSString stringWithFormat:@"%p", self];
}	

@end

@interface NSString(MyStr)
- (NSString*) getPointer;
@end

@implementation NSString(MyStr)

- (NSString*) getPointer {
	return [NSString stringWithFormat:@"%p", self];
}

@end

@interface Test :NSObject

@end

@implementation Test

- (NSString*) description {
	return [NSString stringWithFormat:@"%p", self];
}	

-(void)dealloc{

	[super dealloc];

   NSLog (@"%@",@"desroy a test");
   
}
@end

int main()
{
	// Test* t1 = [Test alloc];
	// NSLog(@"%@",t1);
	// [t1 release];
	// NSString* str = @"dd";
	// NSString* str1 = [str getPointer];
	// NSLog(@"%@",str1);
	NSString* str3 = [[NSNull null] getPointer];
	NSLog(@"%@",str3);
	NSString* str4 = [[NSNull null] getPointer];
	NSLog(@"%@",str4);
	NSLog(@"%@",[[NSNull null] getPointer]);
}

