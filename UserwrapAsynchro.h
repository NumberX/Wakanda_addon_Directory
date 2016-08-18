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
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
	
  explicit UserwrapAsynchro();
  ~UserwrapAsynchro();

  static      Local<Object> CreateUserwrapAsynchro(Isolate* isolate, User* PtUser);
  
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void GetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetDirectorywrapAsynchroWork(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetDirectorywrapAsynchroWorkComplete(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void GetNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetNameAsynchroWork(uv_work_t  *request);

  static void GetNameAsynchroWorkComplete(uv_work_t  *request, int status);
  
  static void BelongsToGroupwrap_1Asynchro(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void BelongsToGroupwrap_1AsynchroWork(uv_work_t  *request);

  static void BelongsToGroupwrap_1AsynchroWorkComplete(uv_work_t  *request, int status);
  
  static void BelongsToGroupwrap_2Asynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void BelongsToGroupwrap_2AsynchroWork(uv_work_t  *request);

  static void BelongsToGroupwrap_2AsynchroWorkComplete(uv_work_t  *request, int status);

  static void IsLoggedInAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void IsLoggedInAsynchroWork(uv_work_t  *request);

  static void IsLoggedInAsynchroWorkComplete(uv_work_t  *request, int status);
 
  static v8::Persistent<v8::Function> constructor;
 
  User *ptuser;
};

}  

#endif