#ifndef MY_FOO_WRAPPER_H
#define MY_FOO_WRAPPER_H

#include "MyFoo.h"

#ifdef __cplusplus
extern "C" {
#endif

// typedef struct MyFoo MyFoo;
MyFoo* create_myfoo();
void destroy_myfoo(MyFoo* mywrapper);
double bar_myfoo(MyFoo* mywrapper, double i, double j);

#ifdef __cplusplus
}
#endif

#endif
