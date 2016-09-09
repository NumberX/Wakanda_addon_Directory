#ifndef Directorywrap_H
#define Directorywrap_H
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include"IDirectory.h"
#include"ControleBasesynchro.h"
#include"ControleDirectorysynchro.h"
#include"Sessionwrap.h"
#include"Utility.h"
using namespace WaDirectory_Controle;
using namespace WaDirectory_Data;
using namespace Tools;
using namespace v8;
using namespace WaDirectory_View;
namespace WaDirectory_View {

	class WaDirectory_Data::IDirectory;
	class Sessionwrap;
	class Userwrap;
	class Groupwrap;
	class Tools::Utility;

class Directorywrap : public node::ObjectWrap {

	friend class Userwrap;
	friend class Groupwrap;
	friend class Sessionwrap;
	friend class ControleBasesynchro;

 public:

	
  static void Init(v8::Local<v8::Object> exports);
  IDirectory* GetDirectory();

 private:

	 static v8::Persistent<v8::Function> constructor;

	 IDirectory *ptdirectory = NULL;


  explicit Directorywrap();
  ~Directorywrap();
  static Local<Boolean> ControleDirectoryUnwrap(Local<Object> handle, Isolate* isolate);
  static v8::Persistent<v8::Value> prototype_Directory_Synchrone;
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void LogIn(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void LogInWork(uv_work_t  *request);
  static void LogInWorkComplete(uv_work_t  *request, int status);
  static void GetGroupwrapNames(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetGroupwrapID(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetGroupwrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetUserwrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetSessionwrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetSessionwrapWork1(uv_work_t  *request);
  static void GetSessionwrapWorkComplete1(uv_work_t  *request, int status);
  static void GetSessionwrapWok2(uv_work_t  *request);
  static void GetSessionwrapWorkComplete2(uv_work_t  *request, int status);
  static void UserwrapBelongTo(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void UserwrapBelongToWork1(uv_work_t  *request);
  static void UserwrapBelongToWorkComplete1(uv_work_t  *request, int status);
  static void UserwrapBelongToWork2(uv_work_t  *request);
  static void UserwrapBelongToWorkComplete2(uv_work_t  *request, int status);
  static void UserwrapBelongToWork3(uv_work_t  *request);
  static void UserwrapBelongToWorkComplete3(uv_work_t  *request, int status);
  static void LogOut(const v8::FunctionCallbackInfo<v8::Value>& args);


public:

	
};

}  

#endif