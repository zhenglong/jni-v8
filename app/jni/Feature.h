#ifndef MY_FOO_H
#define MY_FOO_H

#include "v8.h"
#include "libplatform/libplatform.h"

#include "common.h"

using namespace v8;

class MY_EXPORT Feature {
    public:
		static void InitializeV8();
		static void DestroyV8();
        double Add(double i, double j);
    private:
        static bool _initialized;
        static Platform* _platform;
};

#endif
