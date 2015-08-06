
#define LOG_TAG "BinderDemoClient"
#define LOG_NDEBUG 0

#include <sys/types.h>
#include <unistd.h>

#include <utils/Log.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

#include "BinderDemoService.h"

#define TRACE() ALOGV("[%d] %s", __LINE__, __func__)

using namespace android;

Mutex mLock;
sp<IBinderDemoService> getTestService() {
	TRACE();
	Mutex::Autolock _l(mLock);
	sp<IBinderDemoService> pTestService;
	TRACE();
	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> binder;
	do {
		binder = sm->getService(String16("BinderDemoService"));
		TRACE();
		if (binder != 0)
			break;
		ALOGW("BinderDemoService not published, waiting...");
		usleep(500000); // 0.5 s
	} while(true);

	pTestService = interface_cast<IBinderDemoService>(binder);
	TRACE();
	ALOGE_IF(pTestService==0, "no BinderDemoService!?");
	return pTestService;
}

int main(int argc, char** argv)
{
	sp<IBinderDemoService> pTestService = getTestService();
	ALOGI("[client] running pid=%d,tid=%d\n",getpid(),gettid());
	
	ALOGI("[client] call InitParam\n");
	pTestService->InitParam(new BinderDemoService_CB());
	
	ALOGI("[client] call Add result =%d \n",pTestService->Add(10,20));

	ALOGI("[client] call CallbackTest\n");
	pTestService->CallbackTest();
	ALOGI("[client] end\n");
}


