#ifndef MY_JNI_H
#define MY_JNI_H

#include <jni.h>
#include "wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jdouble JNICALL Java_com_example_hellojni_HelloJni_add(JNIEnv *, jobject, jdouble, jdouble);

#ifdef __cplusplus
}
#endif

#endif
