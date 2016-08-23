#ifndef Userwrap_H
#define Userwrap_H

#include <node.h>
#include <node_object_wrap.h>
#include<string>
#include"User.h"
using namespace WaDirectory;
using namespace v8;
namespace WaDirectorywrap_data_v8 {

class Userwrap : public node::ObjectWrap {
	friend class Directorywrap;
	friend class Sessionwrap;
	friend class Groupwrap;
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
	
  explicit Userwrap();
  ~Userwrap();

  static      Local<Object> CreateUserWrap(Isolate* isolate, User* PtUser, Directorywrap* PtDirectoryWrap);
  
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void GetDirectorywrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void GetName(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void BelongsToGroupwrap_1(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void BelongsToGroupwrap_2(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static void IsLoggedIn(const v8::FunctionCallbackInfo<v8::Value>& args);
  
  static v8::Persistent<v8::Function> constructor;
 
  static Local<Boolean> ControleUserUnwrap(Local<Object> handle, Isolate* isolate);

  static v8::Persistent<v8::Value> prototype_User_Synchrone;

  User *ptuser;
  

  Directorywrap *Pt_DirectoryWrap = NULL;
};

}  

#endif