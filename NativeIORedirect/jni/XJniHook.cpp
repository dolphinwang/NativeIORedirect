#include <stdlib.h>
#include <stddef.h>
#include "XJniHook.h"
#include "core/RedirectManager.h"
#include "Logger.h"


jint Java_com_lody_loadx_client_hook_io_NativeIO_open(JNIEnv* env,jobject thiz) {
	auto &r = kiva::RedirectManager::getInstance();
    r.init();
	return 0;
}


static char* jstringToChar(JNIEnv* env, jstring jstr)
{
       char* rtn = NULL;
       jclass clsstring = env->FindClass("java/lang/String");
       jstring strencode = env->NewStringUTF("utf-8");
       jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
       jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
       jsize alen = env->GetArrayLength(barr);
       jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
       if (alen > 0)
       {
                 rtn = (char*)malloc(alen + 1);
                 memcpy(rtn, ba, alen);
                 rtn[alen] = 0;
       }
       env->ReleaseByteArrayElements(barr, ba, 0);
       return rtn;
}

void Java_com_lody_loadx_client_hook_io_NativeIO_nativeRedirectFolder(JNIEnv* env,jobject thiz, jstring originDir, jstring newDir) {
	auto &r = kiva::RedirectManager::getInstance();
	char* originDirChar = jstringToChar(env, originDir);
	char* newDirChar = jstringToChar(env, newDir);
    LOGD(">>> Mapping Folder [%s] to [%s].", originDirChar, newDirChar);
	r.set(originDirChar, newDirChar, false);
}

void Java_com_lody_loadx_client_hook_io_NativeIO_nativeRedirectFile(JNIEnv* env,jobject thiz, jstring originFilePath, jstring newFilePath) {
  auto &r = kiva::RedirectManager::getInstance();
  char* originFilePathChar = jstringToChar(env, originFilePath);
  char* newFilePathChar = jstringToChar(env, newFilePath);
  LOGD(">>> Mapping File [%s] to [%s].", originFilePathChar, newFilePathChar);
  r.set(originFilePathChar, newFilePathChar, true);
}

