LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

subdirs := $(LOCAL_PATH)/Android.mk
ifeq ($(APP),PNG)
subdirs += $(LOCAL_PATH)/AndroidPNG.mk
else
ifeq ($(APP),GraphicsWindow)
subdirs += $(LOCAL_PATH)/AndroidGraphicsWindow.mk
else
ifeq ($(APP),StateMachine)
subdirs += $(LOCAL_PATH)/AndroidStateMachine.mk
endif
endif
endif

include $(subdirs)