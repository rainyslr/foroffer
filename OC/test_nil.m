#import <Foundation/Foundation.h>

@interface  Test: NSObject

- (void) MakeStrEmpty: (NSString* )str;
@end

@implementation Test

-(void) MakeStrEmpty: (NSString* )str
{
    if ((NSNull *)str == [NSNull null] || str == nil) {
    	NSLog(@"str null");
        str = [[NSString alloc] initWithString:@"new"];
        NSLog(@"retainCount:%ld",str.retainCount);
        [str retain];
        NSLog(@"retainCount:%ld",str.retainCount);
    }
}

@end



int main(int argc, char const *argv[])
{
	NSString* empty  = [[NSString alloc] initWithString:@"new"];
	// 好奇怪啊，为什么下面这一句输出－1啊
	NSLog(@"retainCount of empty:%ld",empty.retainCount);
	// NSString* str_nul = [NSNull null];这一句编译不能通过，类型不兼容
	NSString* str_nul2 = NULL;
	NSString* str_nil = nil;
	NSString* str_Nil = Nil;


	NSLog(@"before:%@",empty);
	NSLog(@"before:%@",str_nul2);
	NSLog(@"before:%@",str_nil);
	NSLog(@"before:%@",str_Nil);



	Test* test = [Test alloc];
	NSLog(@"retainCount of test:%ld",test.retainCount);

	//调用函数之后，三个字符串的内容并不会改变，因为赋值号右边的临时对象被释放了
	[test MakeStrEmpty:empty];
	[test MakeStrEmpty:str_nul2];
	[test MakeStrEmpty:str_nil];
	[test MakeStrEmpty:str_Nil];
	NSLog(@"after:%@",empty);
	NSLog(@"after:%@",str_nul2);//after:(null)
	NSLog(@"after:%@",str_nil);//after:(null)
	NSLog(@"after:%@",str_Nil);//after:(null)


	//如果是直接这样做的话，三个字符串就变成存储空串。
	// str_nul2 = @"";
	// str_nil = @"";
	// str_Nil = @"";
	// NSLog(@"after:%@",empty);
	// NSLog(@"after:%@",str_nul2);
	// NSLog(@"after:%@",str_nil);
	// NSLog(@"after:%@",str_Nil);


    NSObject *obj1 = [NSObject new];
	NSObject *obj2 = nil;
	NSObject *obj3 = [NSObject new];
	NSArray *values1 = [NSArray arrayWithObjects:obj1,obj2,obj3,nil];

	NSLog(@"values1.count:%ld",values1.count);

	NSObject *obj4 = [NSNull null];
	NSArray *values2 = [NSArray arrayWithObjects:obj1,obj4,obj3,nil];
	NSLog(@"values1.count:%ld",values2.count);

	// (NSNull *)obj == [NSNull null]
	return 0;
}