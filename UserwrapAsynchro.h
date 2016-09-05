#ifndef UserwrapAsynchro_H
#define UserwrapAsynchro_H

#include <node.h>
#include <node_object_wrap.h>
#include<string>
#include"User.h"
#include"Utility.h"
#include<uv.h>

using namespace WaDirectorywrap_data_v8;
using namespace WaDirectory;
using namespace v8;
namespace WaDirectorywrapAsynchro_data_v8 {

	class UserwrapAsynchro : public node::ObjectWrap {
	friend class DirectorywrapAsynchro;
	friend class SessionwrapAsynchro;
	friend class GroupwrapAsynchro;
	friend class ControleBaseAsynchro;
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
	
  explicit UserwrapAsynchro();
  ~UserwrapAsynchro();

  static      Local<Object> CreateUserWrapAsynchro(Isolate* isolate, IUser* PtUser, DirectorywrapAsynchro* PtDirectoryWrap);
  
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void GetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetDirectorywrapAsynchroWork(uv_work_t  *request);

  static void GetDirectorywrapAsynchroWorkComplete(uv_work_t  *request, int status);
  
  static void GetNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetNameAsynchroWork(uv_work_t  *request);

  static void GetNameAsynchroWorkComplete(uv_work_t  *request, int status);

  static void BelongsToGroupwrap_1AsynchroWork(uv_work_t  *request);

  static void BelongsToGroupwrap_1AsynchroWorkComplete(uv_work_t  *request, int status);
  
  static void BelongsToGroupwrap_2AsynchroWork(uv_work_t  *request);

  static void BelongsToGroupwrap_2AsynchroWorkComplete(uv_work_t  *request, int status);

  static void IsLoggedInAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void IsLoggedInAsynchroWork(uv_work_t  *request);

  static void IsLoggedInAsynchroWorkComplete(uv_work_t  *request, int status);
 
  static v8::Persistent<v8::Function> constructor;

  static Local<Boolean> ControleUserUnwrap(Local<Object> handle, Isolate* isolate);

  static v8::Persistent<v8::Value> prototype_User_Synchrone;

  static void BelongsToGroupwrapAsynchro(const FunctionCallbackInfo<Value>& args);

  DirectorywrapAsynchro* Pt_DirectorywrapAsynchro;
 
  IUser *ptuser;
};

}  

#endif