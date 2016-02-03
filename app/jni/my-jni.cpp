#include "my-jni.h"

extern "C"
JNIEXPORT jdouble JNICALL Java_com_example_hellojni_HelloJni_add(JNIEnv *, jobject, jdouble, jdouble) {
    MyFoo inst;
    return inst.bar(1, 2);
    // MyFoo* inst = create_myfoo();
    // double result = bar_myfoo(inst, 1, 1);
    // destroy_myfoo(inst);
    // return result;
}
