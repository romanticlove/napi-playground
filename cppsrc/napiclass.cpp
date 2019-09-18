#include "napiclass.h"

Napi::FunctionReference NapiClass::constructor;

Napi::Object NapiClass::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "NapiClass", {
    InstanceMethod("add", &NapiClass::Add),
    InstanceMethod("getValue", &NapiClass::GetValue),
    InstanceMethod("setCb", &NapiClass::SetCb),
    InstanceMethod("runCb", &NapiClass::RunCb)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("NapiClass", func);
  return exports;
}

NapiClass::NapiClass(const Napi::CallbackInfo& info) : Napi::ObjectWrap<NapiClass>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();
  if (length != 1) {
    Napi::TypeError::New(env, "Only one argument expected").ThrowAsJavaScriptException();
  }

  if(!info[0].IsNumber()){
    Napi::Object object_parent = info[0].As<Napi::Object>();
    NapiClass* example_parent = Napi::ObjectWrap<NapiClass>::Unwrap(object_parent);
    SomeClass* parent_actual_class_instance = example_parent->GetInternalInstance();
    this->someClass_ = new SomeClass(parent_actual_class_instance->getValue());
    return;
  }

  Napi::Number value = info[0].As<Napi::Number>();
  this->someClass_ = new SomeClass(value.DoubleValue());
}

Napi::Value NapiClass::GetValue(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  double num = this->someClass_->getValue();
  return Napi::Number::New(env, num);
}

Napi::Value NapiClass::SetCb(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  Napi::Function cb = info[0].As<Napi::Function>();
  this->_cb = Napi::Persistent(cb);

  return Napi::Number::New(env, 1);
}

Napi::Value NapiClass::RunCb(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->_cb.Call(env.Global(), {Napi::String::New(env, "hello world")});
  return Napi::Number::New(env, 1);
}

Napi::Value NapiClass::Add(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (  info.Length() != 1 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  Napi::Number toAdd = info[0].As<Napi::Number>();
  double answer = this->someClass_->add(toAdd.DoubleValue());

  return Napi::Number::New(info.Env(), answer);
}

SomeClass* NapiClass::GetInternalInstance() {
  return this->someClass_;
}