

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := main_BinderDemoClient.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_SHARED_LIBRARIES := liblog libutils libcutils libbinder libBinderDemo libBinderDemoService
LOCAL_MODULE := BinderDemoClient
LOCAL_MODULE_PATH := $(LOCAL_PATH)/..

include $(BUILD_EXECUTABLE)
