
#define LOG_TAG "BinderDemoService"
#define LOG_NDEBUG 0

#include <utils/Log.h>
#include <utils/String16.h>
#include <utils/Errors.h>

#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/MemoryBase.h>
#include <binder/MemoryHeapBase.h>

#include "BinderDemoService.h"

#define TRACE() ALOGV("[%d] %s", __LINE__, __func__)

namespace android {

void BinderDemoService::instantiate() {
	TRACE();
	defaultServiceManager()->addService(
			String16("BinderDemoService"), new BinderDemoService);
}

BinderDemoService::BinderDemoService()
{
	TRACE();
    ALOGI("BinderDemoService started: pid=%d", getpid());
}

BinderDemoService::~BinderDemoService()
{
	TRACE();
}

int BinderDemoService::InitParam(const sp<IBinderDemoService_CB>& callback)
{
	TRACE();
	_callback = callback;
	ALOGI("[service] InitParam pid=%d,tid=%d\n", getpid(), gettid());
	return 0;
}

int BinderDemoService::Add(int a, int b)
{	
	TRACE();
	ALOGI("[service] Add a=%d,b=%d pid=%d,tid=%d\n", a, b, getpid(), gettid());
	return (a+b);
}

int BinderDemoService::CallbackTest()
{
	TRACE();
	ALOGI("[service] CallbackTest pid=%d,tid=%d\n", getpid(), gettid());
	if( _callback.get() )
	{
		printf("[service] call notifyCallback01 \n");
		_callback->notifyCallback01(0, 1, 2);
	}
	return 0;
}

BinderDemoService_CB::BinderDemoService_CB()
{
	TRACE();
}

BinderDemoService_CB::~BinderDemoService_CB()
{
	TRACE();
}

void BinderDemoService_CB::notifyCallback01(int32_t msgType, int32_t ext1, int32_t ext2)
{
	TRACE();
	ALOGI("is call back01: msgType=%d,ext1=%d,ext2=%d pid=%d,tid=%d\n",msgType,ext1,ext2,getpid(),gettid());
}

void BinderDemoService_CB::notifyCallback02(int32_t msgType, const sp<IMemory>& pmem)
{
	TRACE();
	printf("is call back02 pid=%d,tid=%d\n",getpid(),gettid());
}

};//namespace android
//---------------------------------------------------------------------

