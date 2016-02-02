#include "MyWrapper.h"
Handle<Value>
MyWrapper::CallJsFunction(Isolate* isolate, Handle<v8::Object> global, string funcName, Handle<Value> argList[], unsigned int argCount) {
    Handle<Value> js_result;
    Handle<v8::Value> value = global->Get(String::NewFromUtf8(isolate, funcName.c_str()));
    Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
    js_result = func->Call(global, argCount, argList);
    return js_result;
}
void MyWrapper::AddNumberToArguments(Isolate* isolate, double num, Handle<Value> argList[], unsigned int argPos) {
    argList[argPos] = v8::Number::New(isolate, num);
}

double MyWrapper::add(double i, double j) {
	double result = 0;
	Platform* platform = platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();
    ShellArrayBufferAllocator array_buffer_allocator;
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = &array_buffer_allocator;

    Isolate* isolate = Isolate::New(create_params);
    {
        HandleScope handle_scope(isolate);
        Handle<ObjectTemplate> globalTemplate = ObjectTemplate::New(isolate);
        Handle<Context> context = Context::New(isolate, NULL, globalTemplate);
        Context::Scope context_scope(context);

        string s = "function add(i,j) { return (i*j); }";
        Handle<String> source = String::NewFromUtf8(isolate, s.c_str());
        Handle<Script> script = Script::Compile(source);
        script->Run();
        Handle<Value> args[2];
        this->AddNumberToArguments(isolate, 1, args, 0);
        this->AddNumberToArguments(isolate, 100, args, 1);
        Handle<Value> js_result = this->CallJsFunction(isolate, context->Global(), "add", args, 2);
        Handle<Number> num = Handle<Number>::Cast(js_result);
        result = num->Value();
    }
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete platform;
	return result;
}
