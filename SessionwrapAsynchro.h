#ifndef SessionwrapAsynchro_H
#define SessionwrapAsynchro_H
#include <node.h>
#include <node_object_wrap.h>
#include<string>
#include"ISession.h"
#include"Utility.h"
#include<uv.h>

using namespace WaDirectorywrap_data_v8;
using namespace WaDirectory;
using namespace v8;
namespace WaDirectorywrapAsynchro_data_v8{


	class SessionwrapAsynchro : public node::ObjectWrap {

	friend class DirectorywrapAsynchro;
	friend class UserwrapAsynchro;
 public:
  static void Init(v8::Local<v8::Object> exports);
  char *Wsid;
  char *cookies;
  static v8::Persistent<v8::Function> constructor;
  static v8::Persistent<v8::Value> prototype_Session_Synchrone;
  ISession *ptsession;
 private:
	 explicit SessionwrapAsynchro();
  ~SessionwrapAsynchro();
 // static  Local<Value> NewInstance();

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
  static Local<Boolean> ControleSessionUnwrap(Local<Object> handle, Isolate* isolate);
  DirectorywrapAsynchro *Pt_DirectorywrapAsynchro = NULL;
  static       Local<Object> CreateSessionwrapAsynchro(Isolate* isolate, ISession* PtSession, DirectorywrapAsynchro* PtDirectoryWrap);
};

}  // namespace demo

#endif