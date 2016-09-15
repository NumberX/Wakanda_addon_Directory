#ifndef Sessionwrap_H
#define Sessionwrap_H
#include <node.h>
#include<v8.h>
#include <node_object_wrap.h>
#include<string>
#include"Session.h"
#include"Directorywrap.h"
#include"ControleBasesynchro.h"
#include"ControleSessionsynchro.h"
using v8::FunctionTemplate;
using namespace WaDirectory_Controle;
using namespace WaDirectory_Data;
using namespace v8;
namespace WaDirectory_View{

class Sessionwrap : public node::ObjectWrap {
	friend class Directorywrap;
	friend class Userwrap;
	friend class ControleBasesynchro;
 public:
  static void Init(v8::Local<v8::Object> exports);
  
  ISession * GetSessionData();
  char *Wsid;
  
  char *cookies;

  static v8::Persistent<v8::Function> constructor;

  static v8::Persistent<v8::Value> prototype_Session_Synchrone;

  ISession *ptsession;

private:
	 explicit Sessionwrap();
  ~Sessionwrap();

  static      Local<Object> CreateSessionWrap(Isolate* isolate, ISession* PtSession,Directorywrap* PtDirectoryWrap);
  static void NewSession(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetUserwrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetUserwrapWork(uv_work_t  *request);
  static void GetUserwrapWorkComplete(uv_work_t  *request, int status);
  static void GetWASID(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetDirectorywrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void IsValid(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void IsValidWork(uv_work_t  *request);
  static void IsValidWorkComplete(uv_work_t  *request, int status);
  static void LogOut(const v8::FunctionCallbackInfo<v8::Value>& args);
  Directorywrap *Pt_DirectoryWrap = NULL;
  static Local<Boolean> ControleSessionUnwrap(Local<Object> handle, Isolate* isolate);

  ISession* GetSession();

};

}  

#endif