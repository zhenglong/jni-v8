#include "wrapper.h"

MyWrapper* create_mywrapper(){
    return new MyWrapper;
}

void destroy_mywrapper(MyWrapper* mywrapper) {
    delete mywrapper;
 }
 
double add_mywrapper(MyWrapper *mywrapper, double i, double j) {
    return mywrapper->add(i, j);
}
