#ifndef Groupwrap_H
#define Groupwrap_H

#include <node.h>
#include <node_object_wrap.h>
#include"Group.h"
using namespace WaDirectory;
using namespace v8;
namespace WaDirectorywrap_data_v8 {

class Groupwrap : public node::ObjectWrap {
	friend class Directorywrap;
	friend class Userwrap;
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit Groupwrap();
  ~Groupwrap();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetName(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetUserwrapByName(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetSubGroupwrapName(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetDirectorywrap(const v8::FunctionCallbackInfo<v8::Value>& args);

  static  Local<Boolean> ControleGroupUnwrap(Local<Object> handle, Isolate* isolate);

  static v8::Persistent<v8::Value> prototype_Group_Synchrone;
  
  static v8::Persistent<v8::Function> constructor;



  static      Local<Object> CreateGroupWrap(Isolate* isolate, IGroup* PtGroup, Directorywrap* PtDirectoryWrap);

  IGroup *ptgroup=NULL;



  Directorywrap *Pt_DirectoryWrap=NULL;


};

}  

#endif