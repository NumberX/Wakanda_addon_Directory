#ifndef Groupwrap_H
#define Groupwrap_H

#include <node.h>
#include <node_object_wrap.h>
#include"Group.h"
using namespace WaDirectory;
using namespace v8;
namespace WaDirectorywrap_data_v8 {

class Groupwrap : public node::ObjectWrap {
	friend class Directorywrap;
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit Groupwrap();
  ~Groupwrap();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void PlusOne(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetName(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetUserwrapByName(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetSubGroupwrapName(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetDirectorywrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Persistent<v8::Function> constructor;
  static      Local<Object> returnobj(Isolate* isolate, Group* b, uint32_t index);
  Group *ptgroup;
};

}  // namespace demo

#endif