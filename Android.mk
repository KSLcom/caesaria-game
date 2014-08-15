LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

LOCAL_C_INCLUDES := 

# Add your application source files here...
LOCAL_SRC_FILES := libs/SDL/src/main/android/SDL_android_main.c

LOCAL_SHARED_LIBRARIES := SDL2 application
LOCAL_CPP_FEATURES += exceptions
LOCAL_CPP_FEATURES += rtti
LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
