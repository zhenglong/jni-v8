#ifndef MY_JNI_H
#define MY_JNI_H

#include <jni.h>
#include "my-log.h"
#include "MyFoo.h"

#define LOG_TAG "myjni.debug"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jdouble JNICALL Java_com_example_hellojni_HelloJni_add(JNIEnv *, jobject, jdouble, jdouble);

/*
 * Class:     com_example_hellojni_HttpCallback
 * Method:    nativeDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_example_hellojni_HttpCallback_nativeDestroy
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_example_hellojni_HttpCallback
 * Method:    native_onNetworkError
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_example_hellojni_HttpCallback_native_1onNetworkError
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_example_hellojni_HttpCallback
 * Method:    native_onSuccess
 * Signature: (JSLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_example_hellojni_HttpCallback_native_1onSuccess
  (JNIEnv *, jobject, jlong, jshort, jstring);

#ifdef __cplusplus
}
#endif

#endif
