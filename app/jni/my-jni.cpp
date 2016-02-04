#include "my-jni.h"

extern "C"
JNIEXPORT jdouble JNICALL Java_com_example_hellojni_HelloJni_add(JNIEnv* env, jobject thiz, jdouble i, jdouble j) {
    MyFoo inst;
    return inst.bar(i, j);
    // MyFoo* inst = create_myfoo();
    // double result = bar_myfoo(inst, 1, 1);
    // destroy_myfoo(inst);
    // return result;
}
