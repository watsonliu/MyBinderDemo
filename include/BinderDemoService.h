#ifndef BINDERDEMOSERVICE_H
#define BINDERDEMOSERVICE_H

#include "IBinderDemoService.h"

namespace android {

class BinderDemoService : public BnBinderDemoService
{
public:
    BinderDemoService();
    virtual ~BinderDemoService();       
    static void instantiate();
    virtual int InitParam(const sp<IBinderDemoService_CB>& callback) ; //init parameter
    virtual int Add(int a,int b) ; //return a+b
    virtual int CallbackTest() ; //force callback
       
private:     
    sp<IBinderDemoService_CB> _callback;
};

class BinderDemoService_CB : public BnBinderDemoService_CB
{
public:  
    virtual void notifyCallback01(int32_t msgType, int32_t ext1, int32_t ext2); //call from service 
    virtual void notifyCallback02(int32_t msgType, const sp<IMemory>& pmem) ; //test IMemory interface todo
    BinderDemoService_CB();
    virtual ~BinderDemoService_CB();      
};

}; // namespace android

#endif //BINDERDEMOSERVICE_H
//---------------------------------------------------------------------

