MY_LOCAL_PATH := $(call my-dir)
LOCAL_PATH := $(MY_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := libv8
LOCAL_SRC_FILES := ./third_parties/lib/libv8.so
include $(PREBUILT_SHARED_LIBRARY)

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := libv8_libplatform
LOCAL_SRC_FILES := ./third_parties/lib/libv8_libplatform.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := hello-jni
LOCAL_SRC_FILES := MyWrapper.cpp wrapper.cpp my-jni.cpp
LOCAL_SHARED_LIBRARIES := libv8
LOCAL_STATIC_LIBRARIES := libv8_libplatform
LOCAL_CPPFLAGS := \
	-Wall \
	-Wextra \
	-fPIC \
	-fvisibility=hidden \
	-std=c++11 \
	-fexceptions \
	-frtti
LOCAL_C_INCLUDES := $(LOCAL_PATH)/third_parties $(LOCAL_PATH)/third_parties/include
include $(BUILD_SHARED_LIBRARY)

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := hello-jni-test
LOCAL_SRC_FILES := test.cpp
LOCAL_SHARED_LIBRARIES := libv8 hello-jni
LOCAL_CPPFLAGS := \
	-Wall \
	-Wextra \
	-fPIC \
	-fvisibility=hidden \
	-std=c++11 \
	-fexceptions \
	-frtti
LOCAL_C_INCLUDES := $(LOCAL_PATH)/third_parties
include $(BUILD_EXECUTABLE)
