#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>

#include "v8.h"
#include "libplatform/libplatform.h"
using namespace v8;
using namespace std;

/* Header for class hello_CallNative */

#ifndef _Included_hello_CallNative
#define _Included_hello_CallNative

class ShellArrayBufferAllocator : public ArrayBuffer::Allocator {
 public:
  virtual void* Allocate(size_t length) {
    void* data = AllocateUninitialized(length);
    return data == NULL ? data : memset(data, 0, length);
  }
  virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
  virtual void Free(void* data, size_t) { free(data); }
};

class MyWrapper {
    public:
        double add(double i, double j);
    private:
        Handle<Value> CallJsFunction(Isolate* isolate, Handle<v8::Object> global, string funcName, Handle<Value> argList[], unsigned int argCount);
        void AddNumberToArguments(Isolate* isolate, double num, Handle<Value> argList[], unsigned int argPos);
};

#endif
