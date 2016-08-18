#ifndef Directorywrap_H
#define Directorywrap_H
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include"Userwrap.h"
#include"Sessionwrap.h"
#include"Groupwrap.h"
#include"Directory.h"
using namespace WaDirectory;
using namespace v8;
namespace WaDirectorywrap_data_v8 {
	
	class Sessionwrap;
	class Userwrap;
	class Groupwrap;
class Directorywrap : public node::ObjectWrap {

	friend class Userwrap;
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
	
  explicit Directorywrap();
  ~Directorywrap();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void LogIn(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetGroupwrapNames(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetGroupwrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetUserwrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetSessionwrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void UserwrapBelongTo_1(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void UserwrapBelongTo_2(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void UserwrapBelongTo_3(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void LogOut(const v8::FunctionCallbackInfo<v8::Value>& args);
 
  static v8::Persistent<v8::Function> constructor;

  Directory *ptdirectory;
public:

	
};

}  // namespace demo

#endif