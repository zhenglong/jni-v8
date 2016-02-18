#include "Feature.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>

#include "../JsLoader.h"
#include "../my-log.h"

#define LOG_TAG "Feature"

using namespace v8;
using namespace std;

bool Feature::_initialized = false;
Platform* Feature::_platform = NULL;

class ShellArrayBufferAllocator : public ArrayBuffer::Allocator {
 public:
  virtual void* Allocate(size_t length) {
    void* data = AllocateUninitialized(length);
    return data == NULL ? data : memset(data, 0, length);
  }
  virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
  virtual void Free(void* data, size_t) { free(data); }
};

Handle<Value>
CallJsFunction(Isolate* isolate, Handle<v8::Object> global, string funcName, Handle<Value> argList[], unsigned int argCount) {
    Handle<Value> js_result;
    Handle<v8::Value> value = global->Get(String::NewFromUtf8(isolate, funcName.c_str()));
    Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
    js_result = func->Call(global, argCount, argList);
    return js_result;
}
void
AddNumberToArguments(Isolate* isolate, double num, Handle<Value> argList[], unsigned int argPos) {
    argList[argPos] = v8::Number::New(isolate, num);
}

void
Feature::InitializeV8() {
	if (Feature::_initialized) return;

	Platform* platform = platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();
}

void
Feature::DestroyV8() {
    V8::Dispose();
    V8::ShutdownPlatform();
    delete Feature::_platform;
    Feature::_platform = NULL;
    Feature::_initialized = false;
}

double
Feature::Add(double i, double j) {
    double result = 0;
    ShellArrayBufferAllocator array_buffer_allocator;
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = &array_buffer_allocator;

    auto isolate = Isolate::New(create_params);
    {
        HandleScope handle_scope(isolate);
        Handle<ObjectTemplate> globalTemplate = ObjectTemplate::New(isolate);
        Handle<Context> context = Context::New(isolate, NULL, globalTemplate);
        Context::Scope context_scope(context);

        JsLoader jsLoader;
        string s = jsLoader.ReadFile("index.js");
        Handle<String> source = String::NewFromUtf8(isolate, s.c_str());
        Handle<Script> script = Script::Compile(source);
        script->Run();
        Handle<Value> args[2];
        AddNumberToArguments(isolate, i, args, 0);
        AddNumberToArguments(isolate, j, args, 1);
        Handle<Value> js_result = CallJsFunction(isolate, context->Global(), "add", args, 2);
        Handle<Number> num = Handle<Number>::Cast(js_result);
        result = num->Value();
    }
    isolate->Dispose();
	return result;
}
