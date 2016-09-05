#ifndef DirectorywrapAsynchro_H
#define DirectorywrapAsynchro_H
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include"UserwrapAsynchro.h"
#include"SessionwrapAsynchro.h"
#include"GroupwrapAsynchro.h"
#include"Directory.h"
#include"IDirectory.h"
#include"Utility.h"
using namespace WaDirectorywrap_data_v8;
using namespace WaDirectory;
using namespace v8;

namespace WaDirectorywrapAsynchro_data_v8 {
	
	class SessionwrapAsynchro;
	class UserwrapAsynchro;
	class GroupwrapAsynchro;
	class DirectorywrapAsynchro : public node::ObjectWrap {

	friend class ControleBaseAsynchro;
	friend class UserwrapAsynchro;
	friend class SessionwrapAsynchro;
	friend class GroupwrapAsynchro;
 public:
  static void Init(v8::Local<v8::Object> exports);
  static Local<Boolean> ControleDirectoryUnwrap(Local<Object> handle, Isolate* isolate);

 private:
	
  explicit DirectorywrapAsynchro();
  ~DirectorywrapAsynchro();

  static v8::Persistent<v8::Value> prototype_Directory_Synchrone;
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void LogInAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void LogInAsynchroWork(uv_work_t  *request);
  static void LogInAsynchroWorkComplete(uv_work_t  *request, int status);
  static void GetGroupwrapNamesAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetGroupwrapNamesAsynchroWork(uv_work_t  *request);
  static void GetGroupwrapNamesAsynchroWorkComplete(uv_work_t  *request, int status);
  static void GetGroupwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetGroupwrapAsynchroWork(uv_work_t  *request);
  static void GetGroupwrapAsynchroWorkComplete(uv_work_t  *request, int status);
  static void GetUserwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetUserwrapAsynchroWork(uv_work_t  *request);
  static void GetUserwrapAsynchroWorkComplete(uv_work_t  *request, int status);
  static void GetSessionwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetSessionwrapAsynchroWork(uv_work_t  *request);
  static void GetSessionwrapAsynchroWorkComplete(uv_work_t  *request, int status);
  static void UserwrapBelongAsynchroWorkTo_1(uv_work_t  *request);
  static void UserwrapBelongAsynchroWorkCompleteTo_1(uv_work_t  *request, int status);
  static void UserwrapBelongAsynchroWorkTo_2(uv_work_t  *request);
  static void UserwrapBelongAsynchroWorkCompleteTo_2(uv_work_t  *request, int status);
  static void UserwrapBelongAsynchroWorkTo_3(uv_work_t  *request);
  static void UserwrapBelongAsynchroWorkCompleteTo_3(uv_work_t  *request, int status);
 
  static void LogOutAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
 
  static void LogOutAsynchroWork(uv_work_t  *request);
 
  static void LogOutAsynchroWorkComplete(uv_work_t  *request, int status);

  static void UserwrapBelongToAsynchro(const FunctionCallbackInfo<Value>& args);

  static void GetGroupwrapIDAsynchro(const FunctionCallbackInfo<Value>& args);
  static void GetGroupwrapIDAsynchroWork(uv_work_t  *request);
  static void GetGroupwrapIDAsynchroWorkComplete(uv_work_t  *request, int status);
  
  static v8::Persistent<v8::Function> constructor;

  IDirectory *ptdirectory;



};

}  // namespace demo

#endif