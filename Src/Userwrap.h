#ifndef Userwrap_H
#define Userwrap_H

#include <node.h>
#include <node_object_wrap.h>
#include<string>
#include"User.h"
#include"ControleBasesynchro.h"
#include"ControleUsersynchro.h"
#include"ControleUsersynchro.h"
using namespace WaDirectory_Controle;
using namespace WaDirectory_Data;
using namespace v8;
namespace WaDirectory_View {

class Userwrap : public node::ObjectWrap {

	friend class Directorywrap;
	friend class Sessionwrap;
	friend class Groupwrap;
	friend class ControleBasesynchro;
 public:
  static void Init(v8::Local<v8::Object> exports);

  IUser* GetUserData();
 private:
	
  explicit Userwrap();
  ~Userwrap();

  static      Local<Object> CreateUserWrap(Isolate* isolate, IUser* PtUser, Directorywrap* PtDirectoryWrap);
  
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void GetDirectorywrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void GetName(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void BelongsToGroupwrap(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void BelongsToGroupwrapWork1(uv_work_t  *request);

  static void BelongsToGroupwrapWorkComplete1(uv_work_t  *request, int status);

  static void BelongsToGroupwrapWork2(uv_work_t  *request);

  static void BelongsToGroupwrapWorkComplete2(uv_work_t  *request, int status);
  
  static void IsLoggedIn(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void IsLoggedInWork(uv_work_t  *request);

  static void IsLoggedInWorkComplete(uv_work_t  *request, int status);
  
  static v8::Persistent<v8::Function> constructor;
 
  static Local<Boolean> ControleUserUnwrap(Local<Object> handle, Isolate* isolate);

  static v8::Persistent<v8::Value> prototype_User_Synchrone;

  IUser *ptuser;
  

  Directorywrap *Pt_DirectoryWrap = NULL;
};

}  

#endif