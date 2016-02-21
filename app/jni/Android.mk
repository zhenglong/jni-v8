MY_LOCAL_PATH := $(call my-dir)

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := libv8_libbase
LOCAL_SRC_FILES := ./third_parties/lib/libv8_libbase.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := libv8_base
LOCAL_SRC_FILES := ./third_parties/lib/libv8_base.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := libv8_nosnapshot
LOCAL_SRC_FILES := ./third_parties/lib/libv8_nosnapshot.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := libv8_libplatform
LOCAL_SRC_FILES := ./third_parties/lib/libv8_libplatform.a
include $(PREBUILT_STATIC_LIBRARY)

$(info $(MY_LOCAL_PATH))
LOCAL_PATH := $(MY_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := hello-jni
LOCAL_SRC_FILES := my-log.cpp Feature.cpp JsLoader.cpp my-jni.cpp NativeHttpCallback.cpp
LOCAL_STATIC_LIBRARIES := libv8_base libv8_libplatform libv8_libbase libv8_nosnapshot
LOCAL_CPPFLAGS := \
	-Wall \
	-Wextra \
	-fPIC \
	-fvisibility=hidden \
	-std=c++11 \
	-fexceptions \
	-frtti
LOCAL_C_INCLUDES := $(LOCAL_PATH)/foo $(MY_LOCAL_PATH)/third_parties $(MY_LOCAL_PATH)/third_parties/include
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog -landroid
include $(BUILD_SHARED_LIBRARY)

$(info $(MY_LOCAL_PATH))
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
