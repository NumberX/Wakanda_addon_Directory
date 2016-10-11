#ifndef Groupwrap_H
#define Groupwrap_H
#include <node.h>
#include <node_object_wrap.h>
#include"Group.h"
#include"ControleBasesynchro.h"
#include"ControleGroupsynchro.h"
using namespace WaDirectory_Controle;
using namespace WaDirectory_Data;
using namespace v8;
namespace WaDirectory_View {

	class Directorywrap;
	class WaDirectory_Data::IGroup;
class Groupwrap : public node::ObjectWrap {
	friend class Directorywrap;
	friend class Userwrap;
	friend class ControleBasesynchro;
 public:
  static void Init(v8::Local<v8::Object> exports);
  IGroup* GetGroupData();
 private:
  explicit Groupwrap();
  ~Groupwrap();



  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetName(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetId(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetUserwrapByName(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetSubGroupwrapName(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetSubGroupwrapId(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetUserGroupwrapId(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetDirectorywrap(const v8::FunctionCallbackInfo<v8::Value>& args);

  static  Local<Boolean> ControleGroupUnwrap(Local<Object> handle, Isolate* isolate);

  static v8::Persistent<v8::Value> prototype_Group_Synchrone;
  
  static v8::Persistent<v8::Function> constructor;



  static      Local<Object> CreateGroupWrap(Isolate* isolate, IGroup* PtGroup, Directorywrap* PtDirectoryWrap,IDirectory *pt_Directory);

  IGroup *ptgroup=NULL;



  Directorywrap *Pt_DirectoryWrap=NULL;


};

}  

#endif