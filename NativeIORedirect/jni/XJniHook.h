#ifndef __PLUGIN_HOOK_H_
#define __PLUGIN_HOOK_H_
#include <jni.h>


#ifdef __cplusplus
extern "C" {
#endif

jint Java_com_lody_loadx_client_hook_io_NativeIO_open(JNIEnv* env,jobject thiz);

void Java_com_lody_loadx_client_hook_io_NativeIO_nativeRedirectFolder(JNIEnv* env,jobject thiz, jstring originDir, jstring newDir);

void Java_com_lody_loadx_client_hook_io_NativeIO_nativeRedirectFile(JNIEnv* env,jobject thiz, jstring originFilePath, jstring newFilePath);

#ifdef __cplusplus
}
#endif

#endif //__PLUGIN_HOOK_H_
