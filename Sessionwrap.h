#ifndef Sessionwrap_H
#define Sessionwrap_H

#include <node.h>
#include<v8.h>
#include <node_object_wrap.h>
#include<string>
#include"Session.h"
using namespace WaDirectory;
using namespace v8;
namespace WaDirectorywrap_data_v8{
	using v8::Context;
	using v8::Function;
	using v8::FunctionCallbackInfo;
	using v8::FunctionTemplate;
	using v8::Isolate;
	using v8::Local;
	using v8::Number;
	using v8::Object;
	using v8::Persistent;
	using v8::String;
	using v8::Value;
	using v8::Array;

class Sessionwrap : public node::ObjectWrap {
	friend class Directorywrap;
 public:
  static void Init(v8::Local<v8::Object> exports);
  char *Wsid;
  char *cookies;
  static v8::Persistent<v8::Function> constructor;
  static      Local<Object> returnobj(Isolate* isolate, Session* b, uint32_t index);
  Session *ptsession;
 private:
	 explicit Sessionwrap();
  ~Sessionwrap();
 // static  Local<Value> NewInstance();
  
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetUserwrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetWASID(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetDirectorywrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void IsValid(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void LogOut(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void PlusOne(const v8::FunctionCallbackInfo<v8::Value>& args);


};

}  // namespace demo

#endif