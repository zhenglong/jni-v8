#include "my-jni.h"

JNIEXPORT jdouble JNICALL Java_com_example_hellojni_HelloJni_add(JNIEnv *, jobject, jdouble, jdouble) {
    MyWrapper* inst = create_mywrapper();
    double result = add_mywrapper(inst, 1, 1);
    destroy_mywrapper(inst);
    return result;
}
