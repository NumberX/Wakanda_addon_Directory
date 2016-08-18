#include "Groupwrap.h"
#include"Utility.h"
#include<string>
#include<vector>
#include"Group.h"
#include"Userwrap.h"
#include<iostream>
using v8::Value;
using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;

using namespace v8;
using namespace std;
using namespace WaDirectory;
namespace WaDirectorywrap_data_v8 {

Persistent<Function> Groupwrap::constructor;

Groupwrap::Groupwrap() : ptgroup() {
}

Groupwrap::~Groupwrap() {
}
Local<Object> Groupwrap::CreateGroupWrap(Isolate* isolate, Group* PtGroup)
{

	EscapableHandleScope scope(isolate);

	Local<Value> argv[] = { Boolean::New(isolate, true) };
	
	Local<Context> context = isolate->GetCurrentContext();
	
	Local<Function> LocalFunction = Local<Function>::New(isolate, Groupwrap::constructor);
	
	Local<Object> ObjectGroupWrap = LocalFunction->NewInstance(context, 1, argv).ToLocalChecked();
	
	Groupwrap* PtGroupWrap = Groupwrap::Unwrap<Groupwrap>(ObjectGroupWrap);

	PtGroupWrap->ptgroup = PtGroup;

	return scope.Escape(ObjectGroupWrap);



}
void Groupwrap::Init(Local<Object> exports) {

  Isolate* isolate = exports->GetIsolate();

  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  
  tpl->SetClassName(String::NewFromUtf8(isolate, "Groupwrap"));
  
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(tpl, "GetName", GetName);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetUserwrapByName", GetUserwrapByName);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetSubGroupwrapName", GetSubGroupwrapName);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetDirectorywrap", GetDirectorywrap);

  constructor.Reset(isolate, tpl->GetFunction());

  exports->Set(String::NewFromUtf8(isolate, "Groupwrap"),
	  tpl->GetFunction());
}

void Groupwrap::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
	  if (args.Length() == 0) {

		  //Traitement GroupWrap PtGroupWrap=new PtGroupWrap(); 
		  
		  Groupwrap* PtGroupWrap = new Groupwrap();

		  Group *PtGroup = new Group();

		  PtGroupWrap->ptgroup = PtGroup;

		  PtGroupWrap->Wrap(args.Holder());

		  args.GetReturnValue().Set(args.Holder());
	  }
	  else if (args.Length() == 1) { 

		  //Traitement GroupWrap PtGroupWrap=new PtGroupWrap(Group); 

		  Groupwrap* PtGroupWrap = new Groupwrap();

		  PtGroupWrap->Wrap(args.Holder());

		  args.GetReturnValue().Set(args.Holder());
	  }
  } else {
 
  }
}


void Groupwrap::GetName(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();

	Groupwrap* PtGroupWrap = ObjectWrap::Unwrap<Groupwrap>(args.Holder());
	
	std::string resultat = "";
	
	PtGroupWrap->ptgroup->GetName(resultat);

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, resultat.c_str()));
}
void Groupwrap::GetUserwrapByName(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();
	
	std::string res="";
	
	Groupwrap* PtGroupWrap = ObjectWrap::Unwrap<Groupwrap>(args.Holder());
	
	Utility util;
	
	string  user=util.V8Utf8ValueToStdString(args[0]);
	
	User *PtUser = PtGroupWrap->ptgroup->GetUserByName(user);
	
	Local<Object> PtUserWrap = Userwrap::CreateUserWrap(isolate, PtUser);

	args.GetReturnValue().Set(PtUserWrap);
}
void Groupwrap::GetSubGroupwrapName(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();

	Groupwrap* PtGroupWrap = ObjectWrap::Unwrap<Groupwrap>(args.Holder());
	
	std::vector<std::string> resultat;
	
	PtGroupWrap->ptgroup->GetSubGroupName(resultat);
	
	Utility util;

	Local<Array> result_list = util.StdVectorToV8Array(isolate,resultat);

	args.GetReturnValue().Set(result_list);

}
void Groupwrap::GetDirectorywrap(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();

	Groupwrap* obj = ObjectWrap::Unwrap<Groupwrap>(args.Holder());
	
	double x=1;
	
	args.GetReturnValue().Set(Number::New(isolate, x));
}

} 