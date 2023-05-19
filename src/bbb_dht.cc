#include <v8.h>
#include <nan.h>
#include "bbb_dht_read.h"

namespace dht {

  using Nan::FunctionCallbackInfo;
  using Nan::New;
  using Nan::Set;
  using v8::Context;
  using v8::Local;
  using v8::Object;
  using v8::String;
  using v8::Value;
  using v8::Integer;
  using v8::Number;

  void Method(const FunctionCallbackInfo<Value>& args) {
    Local<Context> context = args.GetIsolate()->GetCurrentContext();
    int type = args[0]->Int32Value(context).ToChecked();
    int gpio_base = args[1]->Int32Value(context).ToChecked();
    int gpio_number = args[2]->Int32Value(context).ToChecked();
    float humidity = 0;
    float temperature = 0;
    int result = bbb_dht_read(type, gpio_base, gpio_number, &humidity, &temperature);

    Local<Object> obj = New<Object>();
    Set(obj, New<String>("result").ToLocalChecked(), New<Integer>(result));
    Set(obj, New<String>("humidity").ToLocalChecked(), New<Number>(humidity));
    Set(obj, New<String>("temperature").ToLocalChecked(), New<Number>(temperature));

    args.GetReturnValue().Set(obj);
  }

  void Init(Local<Object> exports) {
    Set(exports, New<String>("read").ToLocalChecked(), FunctionTemplate::New(exports->GetIsolate(), Method)->GetFunction());
  }

  NODE_MODULE(beaglebone_dht, Init)
}
