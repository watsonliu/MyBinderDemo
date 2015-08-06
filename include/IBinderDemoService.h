
#ifndef IBINDERDEMOSERVICE_H
#define IBINDERDEMOSERVICE_H

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>  //for data transact
#include <binder/IMemory.h>

namespace android {

//callback interface ,call by service
class IBinderDemoService_CB : public IInterface
{
public:
    enum {
        CALLBACK01 = IBinder::FIRST_CALL_TRANSACTION,
        CALLBACK02
    };
    DECLARE_META_INTERFACE(BinderDemoService_CB);
    virtual void notifyCallback01(int32_t msgType, int32_t ext1, int32_t ext2) = 0; //call from service 
    virtual void notifyCallback02(int32_t msgType, const sp<IMemory>& pmem) = 0; //test IMemory interface todo
};

class IBinderDemoService : public IInterface
{
public:
    enum {
        SETCALLBACK = IBinder::FIRST_CALL_TRANSACTION,
        ADD,
        CALLBACKTEST
    };
    DECLARE_META_INTERFACE(BinderDemoService);//must need
    virtual int Add(int a, int b) = 0; //return a+b
    virtual int InitParam(const sp<IBinderDemoService_CB>& callback) = 0; //init parameter
    virtual int CallbackTest() = 0; //force callback
};

class BnBinderDemoService: public BnInterface<IBinderDemoService>
{
public:
    virtual status_t onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
};

class BnBinderDemoService_CB: public BnInterface<IBinderDemoService_CB>
{
public:
    virtual status_t onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
};

}; //namespace
#endif //IBINDERDEMOSERVICE_H

