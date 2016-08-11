#include "Directorywrap.h"
#include"Sessionwrap.h"
#include"Directory.h"
#include"Session.h"
#include<vector>
#include<string>
#include<iostream>
namespace WaDirectorywrap_data_v8 {
	using namespace WaDirectory;
	using namespace std;
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
using v8::Value;
using v8::Boolean;
using v8::Array;
using namespace v8;
Persistent<Function> Directorywrap::constructor;

Directorywrap::Directorywrap() :ptdirectory() {

}

Directorywrap::~Directorywrap() {
}

void Directorywrap::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "Directorywrap"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  NODE_SET_PROTOTYPE_METHOD(tpl, "LogIn", LogIn);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetGroupwrapNames", GetGroupwrapNames);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetGroupwrap", GetGroupwrap);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetUserwrap", GetUserwrap);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetSessionwrap", GetSessionwrap);
  NODE_SET_PROTOTYPE_METHOD(tpl, "UserwrapBelongTo_1", UserwrapBelongTo_1);
  NODE_SET_PROTOTYPE_METHOD(tpl, "UserwrapBelongTo_2", UserwrapBelongTo_2);
  NODE_SET_PROTOTYPE_METHOD(tpl, "UserwrapBelongTo_3", UserwrapBelongTo_3);
  NODE_SET_PROTOTYPE_METHOD(tpl, "LogOut", LogOut);
  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "Directorywrap"),
               tpl->GetFunction());
}

void Directorywrap::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
    if (args.Length() == 0) {
		Directorywrap* pw = new Directorywrap();
		Directory *p = new Directory();
		pw->ptdirectory = p;
		pw->Wrap(args.This());
		args.GetReturnValue().Set(args.This());
	}
	else if (args.Length() == 1) { // we have a Directory object allocated
		Directorywrap* pw = new Directorywrap();
		pw->Wrap(args.This());
		args.GetReturnValue().Set(args.This());
	}

  } else {
  }
}

void Directorywrap::LogIn(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	const int argc =1 ;
	Directorywrap* pt = ObjectWrap::Unwrap<Directorywrap>(args.This());
	 String::Utf8Value userv8(args[0]); String::Utf8Value passwordv8(args[1]);
	//user = String::Utf8Value(args[0]);
	 string user(*userv8), password(*passwordv8);
	Session *s = pt->ptdirectory->LogIn(user,password);
	uint32_t v = 1;
	Local<Object> objsess = Sessionwrap::returnobj(isolate, s, v);

	args.GetReturnValue().Set(objsess);
	
}
void Directorywrap::GetGroupwrapNames(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Directorywrap* obj = ObjectWrap::Unwrap<Directorywrap>(args.Holder());
	
	std::vector<std::string> resultat; obj->ptdirectory->GetGroupNames(resultat);
	//resultat.push_back("Resultat 1"); resultat.push_back("Resultat 2"); resultat.push_back("Resultat 3");
	Local<Array> result_list = Array::New(isolate);
	for (unsigned int i = 0; i < resultat.size(); i++) {
		Local<String> result = String::NewFromUtf8(isolate, resultat[i].c_str());

		result_list->Set(i, result);
	}
	args.GetReturnValue().Set(result_list);
}
void Directorywrap::GetGroupwrap(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	Directorywrap* obj = ObjectWrap::Unwrap<Directorywrap>(args.Holder());
	String::Utf8Value groupid(args[0]); string groupidf(*groupid);
	Group* ptgroup = obj->ptdirectory->GetGroup(groupidf);
	uint32_t v = 1;
	Local<Object> localobj = Groupwrap::returnobj(isolate, ptgroup, v);
	args.GetReturnValue().Set(localobj);


}
void Directorywrap::GetUserwrap(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	//return value
	const int argc = 1;
	Local<Value> argv[argc] = { args[0] };
	Local<Context> context = isolate->GetCurrentContext();
	Local<Function> cons = Local<Function>::New(isolate, Userwrap::constructor);
	Local<Object> result =
		cons->NewInstance(context, argc, argv).ToLocalChecked();
	args.GetReturnValue().Set(result);
}
void Directorywrap::GetSessionwrap(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	//return value
	const int argc = 1;
	Local<Value> argv[argc] = { args[0] };
	Local<Context> context = isolate->GetCurrentContext();
	Local<Function> cons = Local<Function>::New(isolate, Sessionwrap::constructor);
	Local<Object> result =
		cons->NewInstance(context, argc, argv).ToLocalChecked();
	args.GetReturnValue().Set(result);
}
void Directorywrap::UserwrapBelongTo_1(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Directorywrap* obj = ObjectWrap::Unwrap<Directorywrap>(args.Holder());
	
	bool resultat = true;
	args.GetReturnValue().Set(Boolean::New(isolate, resultat));
}
void Directorywrap::UserwrapBelongTo_2(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Directorywrap* obj = ObjectWrap::Unwrap<Directorywrap>(args.Holder());
	
	bool resultat = true;
	args.GetReturnValue().Set(Boolean::New(isolate, resultat));
}
void Directorywrap::UserwrapBelongTo_3(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Directorywrap* obj = ObjectWrap::Unwrap<Directorywrap>(args.Holder());
	
	bool resultat = true;
	args.GetReturnValue().Set(Boolean::New(isolate, resultat));
}
void Directorywrap::LogOut(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Directorywrap* obj = ObjectWrap::Unwrap<Directorywrap>(args.Holder());
	
	bool resultat = true;
	args.GetReturnValue().Set(Boolean::New(isolate, resultat));
}
} 