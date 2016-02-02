#include "MyWrapper.h"

#ifndef WRAPPER_H
#define WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MyWrapper MyWrapper;
MyWrapper* create_mywrapper();
void destroy_mywrapper(MyWrapper* mywrapper);
double add_mywrapper(MyWrapper *mywrapper, double i, double j);

#ifdef __cplusplus
}
#endif

#endif
