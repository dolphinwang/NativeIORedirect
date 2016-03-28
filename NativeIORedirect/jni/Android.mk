LOCAL_PATH := $(call my-dir) 
include $(CLEAR_VARS)
LOCAL_MODULE    := xhook
LOCAL_SRC_FILES := core/RedirectManager.cpp core/IOHook.cpp XJniHook.cpp hooklib/elf_common.cpp hooklib/elf_hooker.cpp hooklib/elf_module.cpp
LOCAL_LDLIBS	:= -llog
include $(BUILD_SHARED_LIBRARY)