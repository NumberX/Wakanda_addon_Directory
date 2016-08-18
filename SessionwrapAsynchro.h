#ifndef SessionwrapAsynchro_H
#define SessionwrapAsynchro_H
#include<uv.h>
#include <node.h>
#include<v8.h>
#include <node_object_wrap.h>
#include"Work.h"
#include"Thread_Data.h"
#include"Work.h"
#include"Session.h"
#include"Utility.h"
using namespace WaDirectorywrap_data_v8;
using namespace WaDirectory;
using namespace v8;
namespace WaDirectorywrapAsynchro_data_v8{
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

	class SessionwrapAsynchro : public node::ObjectWrap {

	friend class DirectorywrapAsynchro;
 public:
  static void Init(v8::Local<v8::Object> exports);
  char *Wsid;
  char *cookies;
  static v8::Persistent<v8::Function> constructor;

  Session *ptsession;
 private:
	 explicit SessionwrapAsynchro();
  ~SessionwrapAsynchro();
 // static  Local<Value> NewInstance();
  static      Local<Object> CreateSessionwrapAsynchro(Isolate* isolate, Session* PtSession);
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetUserwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetUserwrapAsynchroWork(uv_work_t  *request);
  static void GetUserwrapAsynchroWorkComplete(uv_work_t  *request, int status);
  static void GetWASIDAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetWASIDAsynchroWork(uv_work_t  *request);
  static void GetWASIDAsynchroWorkComplete(uv_work_t  *request, int status);
  static void GetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetDirectorywrapAsynchroWork(uv_work_t  *request);
  static void GetDirectorywrapAsynchroWorkComplete(uv_work_t  *request, int status);
  static void IsValidAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void IsValidAsynchroWork(uv_work_t  *request);
  static void IsValidAsynchroWorkComplete(uv_work_t  *request, int status);
  static void LogOutAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void LogOutAsynchroWork(uv_work_t  *request);
  static void LogOutAsynchroWorkComplete(uv_work_t  *request, int status);
};

}  // namespace demo

#endif