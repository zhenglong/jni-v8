#include "my-jni.h"
#include <string>
#include "NativeHttpCallback.h"
#include "JsLoader.h"

using namespace std;

jobject createJavaHttpCallback(JNIEnv* env) {
    auto nativeHttpCallback = new NativeHttpCallback();
    string clsName = "com/example/hellojni/HttpCallback";
    jclass cls = env->FindClass(clsName.c_str());
    jmethodID constructor = env->GetMethodID(cls, "<init>", "(J)V");
    return env->NewObject(cls, constructor, reinterpret_cast<long>(nativeHttpCallback));
}

void callJavaHttpGet(JNIEnv* env, const string& url) {
    string clsName = "com/example/hellojni/AndroidHttp";
    string methodName = "get";
    auto httpCallback = createJavaHttpCallback(env);
    jclass cls = env->FindClass(clsName.c_str());
    jmethodID constructor = env->GetMethodID(cls, "<init>", "()V");
    jmethodID getMethod = env->GetMethodID(cls, methodName.c_str(), "(Ljava/lang/String;Lcom/example/hellojni/HttpCallback;)V");
    jobject inst = env->NewObject(cls, constructor);
    jstring s = env->NewStringUTF(url.c_str());
    env->CallVoidMethod(inst, getMethod, s, httpCallback);
}

NativeHttpCallback* getNativeHttpCallback(long nativeRef) {
    return reinterpret_cast<NativeHttpCallback*>(nativeRef);
}

extern "C"
JNIEXPORT jdouble JNICALL Java_com_example_hellojni_HelloJni_add(JNIEnv* env, jobject thiz, jdouble i, jdouble j) {
    //JsLoader::env = env;
    //MyFoo inst;
    //return inst.bar(i, j);
    return 100;

	//callJavaHttpGet(env, "http://www.test.com/api/foobar");
	//return 1;

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
    LOGD(LOG_TAG, "delete:%ld", nativeRef);
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
    auto dataStr = env->GetStringUTFChars(data, 0);
	LOGD(LOG_TAG, "status: %d, data: %s", httpStatus, dataStr);
    obj->onSuccess(httpStatus, dataStr);
    env->ReleaseStringUTFChars(data, dataStr);
}

extern "C"
JNIEXPORT void JNICALL Java_com_example_hellojni_HelloJni_loadAssetManager
	(JNIEnv *env, jobject thiz, jobject assetManager) {
	JsLoader::AssetManager = env->NewGlobalRef(assetManager);
}

extern "C"
JNIEXPORT void JNICALL Java_com_example_hellojni_HelloJni_unloadAssetManager
  (JNIEnv *env, jobject thiz) {
	if (NULL != JsLoader::AssetManager) {
		env->DeleteGlobalRef(JsLoader::AssetManager);
		JsLoader::AssetManager = NULL;
        JsLoader::env = NULL;
	}
}
