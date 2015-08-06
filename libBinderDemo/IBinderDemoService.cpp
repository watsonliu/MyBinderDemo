
#define LOG_TAG "IBinderDemoService"
#define LOG_NDEBUG 0

#include <stdint.h>
#include <sys/types.h>

#include <utils/Log.h>

#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

#include "IBinderDemoService.h"

#define TRACE() ALOGV("[%d] %s", __LINE__, __func__)

namespace android {

class BpBinderDemoService: public BpInterface<IBinderDemoService>
{
public:
    BpBinderDemoService(const sp<IBinder>& impl)
        : BpInterface<IBinderDemoService>(impl)
    {
    	TRACE();
    }
	
    virtual int InitParam(const sp<IBinderDemoService_CB>& callback) //init parameter
	{
		TRACE();
		Parcel data, reply;
		data.writeInterfaceToken(IBinderDemoService::getInterfaceDescriptor()); 
		data.writeStrongBinder(callback->asBinder());
		remote()->transact(IBinderDemoService::SETCALLBACK, data, &reply);
		return (reply.readInt32());
	}
	
	virtual int Add(int a,int b) //return a+b
	{
		TRACE();
		Parcel data, reply;
		data.writeInterfaceToken(IBinderDemoService::getInterfaceDescriptor()); 
		data.writeInt32(a); 
		data.writeInt32(b);
		remote()->transact(IBinderDemoService::ADD, data, &reply);
		return (reply.readInt32());
	}
	
	virtual int CallbackTest() //force callback
	{
		TRACE();
		Parcel data, reply;
		data.writeInterfaceToken(IBinderDemoService::getInterfaceDescriptor()); 
		remote()->transact(IBinderDemoService::CALLBACKTEST, data, &reply);
		return (reply.readInt32());
	}
};
IMPLEMENT_META_INTERFACE(BinderDemoService, "android.IBinderDemoService");

status_t BnBinderDemoService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
	TRACE();
	switch(code) {
	case SETCALLBACK: {
		CHECK_INTERFACE(IBinderDemoService, data, reply);//adapt to data.writeInterfaceToken
		sp<IBinderDemoService_CB> callback = interface_cast<IBinderDemoService_CB>(data.readStrongBinder());
		reply->writeInt32(InitParam(callback));
		return NO_ERROR;
		} break;
	case ADD: {
		CHECK_INTERFACE(IBinderDemoService, data, reply);
		int a = data.readInt32();
		int b = data.readInt32();
		reply->writeInt32(Add(a,b));
		return NO_ERROR;
		} break;
	case CALLBACKTEST: {
		CHECK_INTERFACE(IBinderDemoService, data, reply);
		reply->writeInt32(CallbackTest());
		return NO_ERROR;
		} break;
	default:
		return BBinder::onTransact(code, data, reply, flags);
	}
}


class BpBinderDemoService_CB: public BpInterface<IBinderDemoService_CB>
{
public:
    BpBinderDemoService_CB(const sp<IBinder>& impl)
        : BpInterface<IBinderDemoService_CB>(impl)
    {
    	TRACE();
    }
	
	virtual void notifyCallback01(int32_t msgType, int32_t ext1, int32_t ext2)
	{
		TRACE();
		Parcel data, reply;
		data.writeInterfaceToken(IBinderDemoService_CB::getInterfaceDescriptor()); 
		data.writeInt32(msgType);
		data.writeInt32(ext1);
		data.writeInt32(ext2);
		remote()->transact(IBinderDemoService_CB::CALLBACK01, data, &reply);
	}
	
	virtual void notifyCallback02(int32_t msgType, const sp<IMemory>& pmem) 
	{
		TRACE();
		Parcel data, reply;
		data.writeInterfaceToken(IBinderDemoService_CB::getInterfaceDescriptor()); //why do that?? todo
		data.writeInt32(msgType); 
		data.writeStrongBinder(pmem->asBinder());
		remote()->transact(IBinderDemoService_CB::CALLBACK02, data, &reply);
	}
};
IMPLEMENT_META_INTERFACE(BinderDemoService_CB, "android.IBinderDemoService_CB");

status_t BnBinderDemoService_CB::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
	TRACE();
	switch(code) {
	case CALLBACK01: {
		CHECK_INTERFACE(IBinderDemoService_CB, data, reply);
		int32_t msgType = data.readInt32();
		int32_t ext1 = data.readInt32();
		int32_t ext2 = data.readInt32();
		notifyCallback01(msgType, ext1, ext2);
		return NO_ERROR;
		} break;
	case CALLBACK02: {
		CHECK_INTERFACE(IBinderDemoService_CB, data, reply);
		int32_t msgType = data.readInt32();
		sp<IMemory> pmem = interface_cast<IMemory>(data.readStrongBinder());
		notifyCallback02(msgType, pmem);
		return NO_ERROR;
		} break;
	default:
		return BBinder::onTransact(code, data, reply, flags);
	}
}
// ----------------------------------------------------------------------------
}; // namespace android

