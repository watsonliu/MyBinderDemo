LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := IBinderDemoService.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_SHARED_LIBRARIES := libutils liblog libbinder
LOCAL_MODULE := libBinderDemo
LOCAL_MODULE_PATH := $(LOCAL_PATH)/..

include $(BUILD_SHARED_LIBRARY)
