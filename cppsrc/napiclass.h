#include <napi.h>
#include "someclass.h"

class NapiClass : public Napi::ObjectWrap<NapiClass> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports); //Init function for setting the export key to JS
  NapiClass(const Napi::CallbackInfo& info); //Constructor to initialise
  SomeClass* GetInternalInstance();
  Napi::FunctionReference _cb;
 private:
  static Napi::FunctionReference constructor; //reference to store the class definition that needs to be exported to JS
  Napi::Value GetValue(const Napi::CallbackInfo& info); //wrapped getValue function 
  Napi::Value Add(const Napi::CallbackInfo& info); //wrapped add function
  Napi::Value SetCb(const Napi::CallbackInfo& info);
  Napi::Value RunCb(const Napi::CallbackInfo& info);
  SomeClass *someClass_; //internal instance of actualclass used to perform actual operations.
};