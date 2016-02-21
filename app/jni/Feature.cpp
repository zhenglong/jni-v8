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

Local<Value>
CallJsFunction(Isolate* isolate, Handle<v8::Object> global, string funcName, Handle<Value> argList[], unsigned int argCount) {
	auto context = isolate->GetCurrentContext();
    Local<Value> js_result;
    Local<v8::Value> value = global->Get(context, String::NewFromUtf8(isolate, funcName.c_str(), NewStringType::kInternalized).ToLocalChecked()).ToLocalChecked();
    Local<v8::Function> func = v8::Local<v8::Function>::Cast(value);
    js_result = func->Call(context, global, argCount, argList).ToLocalChecked();
    return js_result;
}
void
AddNumberToArguments(Isolate* isolate, double num, Local<Value> argList[], unsigned int argPos) {
    argList[argPos] = v8::Number::New(isolate, num);
}

void
Feature::InitializeV8() {
	if (Feature::_initialized) return;

	Platform* platform = platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();

    ShellArrayBufferAllocator array_buffer_allocator;
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = &array_buffer_allocator;

    auto isolate = Isolate::New(create_params);
	isolate->Enter();
}

void
Feature::DestroyV8() {
	auto isolate = Isolate::GetCurrent();
	isolate->Exit();
	isolate->Dispose();

    V8::Dispose();
    V8::ShutdownPlatform();
    delete Feature::_platform;
    Feature::_platform = NULL;
    Feature::_initialized = false;
}

double
Feature::Add(double i, double j) {
    double result = 0;
	auto isolate = Isolate::GetCurrent();
	if (isolate == NULL) {
		LOGD(LOG_TAG, "isolate current is null");
		return -1;
	}
    {
        HandleScope handle_scope(isolate);
		Local<Context> context = isolate->GetCurrentContext();
		if (context.IsEmpty()) {
			context = Context::New(isolate);
			context->Enter();
		}
        Context::Scope context_scope(context);

        JsLoader jsLoader;
		string s = jsLoader.ReadFile("index.js");
		LOGD(LOG_TAG, "%s", s.c_str());
		Local<String> source = String::NewFromUtf8(isolate, s.c_str(), NewStringType::kInternalized).ToLocalChecked();
		Local<Script> script;
		if (!Script::Compile(context, source).ToLocal(&script)) {
			LOGD(LOG_TAG, "script local is empty");
		}
		script->Run();
		Handle<Value> args[2];
		AddNumberToArguments(isolate, i, args, 0);
		AddNumberToArguments(isolate, j, args, 1);
		auto global = context->Global();
		Local<Value> js_result = CallJsFunction(isolate, global, "add", args, 2);
		Local<Number> num = Local<Number>::Cast(js_result);
		result = num->Value();
    }
	return result;
}
