#include "my-jni.h"

jobject createJavaHttpCallback(JNIEnv* env) {
    auto nativeHttpCallback = new NativeHttpCallback();
    string clsName = "com/example/hellojni/HttpCallback";
    jobject cls = env->FindClass(env, clsName);
    jmehotdID constructor = env->GetMethodID(env, cls, "<init>", "(J)V");
    return env->NewObject(env, cls, constructor, reinterpret_cast<long>(nativeHttpCallback));
}

void callJavaHttpGet(JNIEnv* env, const string& url) {
    string clsName = "com/example/hellojni/AndroidHttp";
    string methodName = "get";
    auto httpCallback = createJavaHttpCallback(env);
    jobject cls = env->FindClass(env, clsName);
    jmehotdID constructor = env->GetMethodID(env, cls, "<init>", "()V");
    jmehotdID getMethod = env->GetMethodID(env, cls, methodName, "(Ljava/lang/String;Lcom/example/hellojni/HttpCallback;)V");
    jobject inst = env->NewObject(env, cls, constructor);
    jString s = env->NewStringUTF(env, url);
    env->CallVoidMethod(env, inst, getMethod, s, httpCallback);
}

NativeHttpCallback* getNativeHttpCallback(long nativeRef) {
    return reinterpret_cast<NativeHttpCallback*>(nativeRef);
}

extern "C"
JNIEXPORT jdouble JNICALL Java_com_example_hellojni_HelloJni_add(JNIEnv* env, jobject thiz, jdouble i, jdouble j) {
    //MyFoo inst;
    //return inst.bar(i, j);
    //
    


    //
    // MyFoo* inst = create_myfoo();
    // double result = bar_myfoo(inst, 1, 1);
    // destroy_myfoo(inst);
    // return result;
}

extern "C"
JNIEXPORT void JNICALL Java_com_example_hellojni_HttpCallback_nativeDestroy
  (JNIEnv *env, jobject thiz, jlong nativeRef) {
    auto obj = getNativeHttpCallback(nativeRef);
    delete obj;
}


extern "C"
JNIEXPORT void JNICALL Java_com_example_hellojni_HttpCallback_native_1onNetworkError
  (JNIEnv *env, jobject thiz, jlong nativeRef) {
    auto obj = getNativeHttpCallback(nativeRef);
    obj->onNetworkError();
}

extern "C"
JNIEXPORT void JNICALL Java_com_example_hellojni_HttpCallback_native_1onSuccess
  (JNIEnv *env, jobject thiz, jlong nativeRef, jshort httpStatus, jstring data) {
    auto obj = getNativeHttpCallback(nativeRef);
    auto dataStr = env->GetStringUTFChars(ENV, data, 0);
    obj->onSuccess(httpStatus, dataStr);
    env->ReleaseStringUTFChars(env, data, dataStr);
}
