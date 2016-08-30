#ifndef Directorywrap_H
#define Directorywrap_H
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include"Userwrap.h"
#include"Sessionwrap.h"
#include"Groupwrap.h"
#include"Directory.h"
#include"IDirectory.h"
using namespace WaDirectory;
using namespace v8;
namespace WaDirectorywrap_data_v8 {
	
	class Sessionwrap;
	class Userwrap;
	class Groupwrap;
class Directorywrap : public node::ObjectWrap {

	friend class Userwrap;
	friend class Groupwrap;
	friend class Sessionwrap;

 public:

	
  static void Init(v8::Local<v8::Object> exports);
  IDirectory* GetDirectory();

 private:
	
  explicit Directorywrap();
  ~Directorywrap();
  static Local<Boolean> ControleDirectoryUnwrap(Local<Object> handle, Isolate* isolate);
  static v8::Persistent<v8::Value> prototype_Directory_Synchrone;
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void LogIn(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetGroupwrapNames(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetGroupwrapID(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetGroupwrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetUserwrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetSessionwrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void UserwrapBelongTo(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void LogOut(const v8::FunctionCallbackInfo<v8::Value>& args);

  
  static v8::Persistent<v8::Function> constructor;

  IDirectory *ptdirectory = NULL;

public:

	
};

}  // namespace demo

#endif