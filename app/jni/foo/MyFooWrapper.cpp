#include "MyFooWrapper.h"

MyFoo* create_myfoo(){
    return new MyFoo;
}

void destroy_myfoo(MyFoo* myfoo) {
    delete myfoo;
 }

double bar_myfoo(MyFoo* myfoo, double i, double j) {
    return myfoo->bar(i, j);
}
