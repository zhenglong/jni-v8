#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
extern "C" jdouble JNICALL Java_com_example_hellojni_HelloJni_add(JNIEnv *env, jobject instance, jdouble i, jdouble j);

int main(int argc, char* argv[]) {
    printf("%f\n", Java_com_example_hellojni_HelloJni_add(NULL, NULL, 1, 101));
    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// //#include <cstring>
// #include <string>
// #include <jni.h>
//
// #include "include/libplatform/libplatform.h"
// #include "include/v8.h"
//
// using namespace v8;
// using namespace std;
//
// class ShellArrayBufferAllocator : public ArrayBuffer::Allocator {
//  public:
//   virtual void* Allocate(size_t length) {
//     void* data = AllocateUninitialized(length);
//     return data == NULL ? data : memset(data, 0, length);
//   }
//   virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
//   virtual void Free(void* data, size_t) { free(data); }
// };
// Handle<v8::Value> CallJsFunction(Isolate* isolate, Handle<v8::Object> global, string funcName, Handle<Value> argList[], unsigned int argCount) {
//     Handle<Value> js_result;
//     Handle<v8::Value> value = global->Get(String::NewFromUtf8(isolate, funcName.c_str()));
//     Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
//     js_result = func->Call(global, argCount, argList);
//     return js_result;
// }
// void AddNumberToArguments(Isolate* isolate, double num, Handle<Value> argList[], unsigned int argPos) {
//     argList[argPos] = v8::Number::New(isolate, num);
// }
// int main(int argc, char* argv[]) {
//     Platform* platform = platform::CreateDefaultPlatform();
//     V8::InitializePlatform(platform);
//     V8::Initialize();
//     ShellArrayBufferAllocator array_buffer_allocator;
//     v8::Isolate::CreateParams create_params;
//     create_params.array_buffer_allocator = &array_buffer_allocator;
//
//     Isolate* isolate = Isolate::New(create_params);
//     {
//         HandleScope handle_scope(isolate);
//         Handle<ObjectTemplate> globalTemplate = ObjectTemplate::New(isolate);
//         Handle<Context> context = Context::New(isolate, NULL, globalTemplate);
//         Context::Scope context_scope(context);
//
//         string s = "function add(i,j) { return (i*j); }";
//         Handle<String> source = String::NewFromUtf8(isolate, s.c_str());
//         Handle<Script> script = Script::Compile(source);
//         script->Run();
//         Handle<Value> args[2];
//         AddNumberToArguments(isolate, 1, args, 0);
//         AddNumberToArguments(isolate, 100, args, 1);
//         Handle<Value> js_result = CallJsFunction(isolate, context->Global(), "add", args, 2);
//         Handle<Number> num = Handle<Number>::Cast(js_result);
//         printf("%f\n", num->Value());
//     }
//     isolate->Dispose();
//     V8::Dispose();
//     V8::ShutdownPlatform();
//     delete platform;
//     return 0;
// }
