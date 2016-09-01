#ifndef GroupwrapAsynchro_H
#define GroupwrapAsynchro_H

#include <node.h>
#include <node_object_wrap.h>
#include <uv.h>
#include"Group.h"
#include"Utility.h"
using namespace WaDirectorywrap_data_v8;
using namespace WaDirectory;
using namespace v8;
namespace WaDirectorywrapAsynchro_data_v8 {
	class GroupwrapAsynchro : public node::ObjectWrap {
	friend class DirectorywrapAsynchro;
	friend class UserwrapAsynchro;
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit GroupwrapAsynchro();
  ~GroupwrapAsynchro();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetNameAsynchroWork(uv_work_t  *request);

  static void GetNameAsynchroWorkComplete(uv_work_t  *request, int status);

  static void GetUserwrapByNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetUserwrapByNameAsynchroWork(uv_work_t  *request);

  static void GetUserwrapByNameAsynchroWorkComplete(uv_work_t  *request, int status);

  static void GetSubGroupwrapNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetSubGroupwrapNameAsynchroWork(uv_work_t  *request);

  static void GetSubGroupwrapNameAsynchroWorkComplete(uv_work_t  *request, int status);

  static void GetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetDirectorywrapAsynchroWork(uv_work_t  *request);

  static void GetDirectorywrapAsynchroWorkComplete(uv_work_t  *request, int status);

  static  Local<Boolean> ControleGroupUnwrap(Local<Object> handle, Isolate* isolate);

  static v8::Persistent<v8::Function> constructor;

  static v8::Persistent<v8::Value> prototype_Group_Synchrone;

  static      Local<Object> CreateGroupwrapAsynchro(Isolate* isolate, IGroup* PtGroup, DirectorywrapAsynchro* PtDirectoryWrap);

  IGroup *ptgroup;
  DirectorywrapAsynchro* PtDirectoryWrapAsynchro;

};

}  // namespace demo

#endif