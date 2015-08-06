基于android4.4.2

目录说明如下：
include 
头文件

libBinderDemo
BinderDemoService的binder接口，编译生成libBinderDemo.so

libBinderDemoService
BinderDemoService的具体实现，编译生成libBinderDemoService.so

BinderDemoServer
BinderDemo的服务端，编译生成binderdemoServer

test
BinderDemo的测试客户端，编译生成BinderDemoClient


logcat -v time -s IBinderDemoService BinderDemoService BinderDemoServer BinderDemoClient
