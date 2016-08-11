#include "Sessionwrap.h"
#include "Userwrap.h"
#include<string>
#include<iostream>
#include"Session.h"
using namespace WaDirectory;
using namespace std;
namespace WaDirectorywrap_data_v8 {
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
using v8::Handle;
using v8::HandleScope;
using namespace v8;
Persistent<Function> Sessionwrap::constructor;

Sessionwrap::Sessionwrap():ptsession()  {
	
}

Sessionwrap::~Sessionwrap() {
}
Local<Object> Sessionwrap::returnobj(Isolate* isolate, Session* b, uint32_t index)
{
	EscapableHandleScope scope(isolate);

	// Get a new instance of PersonWrap
	Local<Value> argv[] = { Boolean::New(isolate, true) };
	Local<Context> context = isolate->GetCurrentContext();
	Local<Function> cons = Local<Function>::New(isolate, Sessionwrap::constructor);
	Local<Object> obj = cons->NewInstance(context, 1, argv).ToLocalChecked();
	Sessionwrap* pw = Sessionwrap::Unwrap<Sessionwrap>(obj);

	 pw->ptsession= b;

	return scope.Escape(obj);



}
void Sessionwrap::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "Sessionwrap"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetUserwrap", GetUserwrap);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetWASID", GetWASID);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetDirectorywrap", GetDirectorywrap);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsValid", IsValid);
  NODE_SET_PROTOTYPE_METHOD(tpl, "LogOut", LogOut);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "Sessionwrap"),
               tpl->GetFunction());
}

void Sessionwrap::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
	  if (args.Length() == 0) {
		  Sessionwrap* pw = new Sessionwrap();
		  Session *p = new Session();
		  pw->ptsession = p;
		  pw->Wrap(args.This());
		  args.GetReturnValue().Set(args.This());
	  }
	  else if (args.Length() == 1) { // we have a Directory object allocated
		  Sessionwrap* pw = new Sessionwrap();
		  pw->Wrap(args.This());
		  args.GetReturnValue().Set(args.This());
	  }
  } else {
    
  }
}


void Sessionwrap::GetUserwrap(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();


	Sessionwrap* pt = ObjectWrap::Unwrap<Sessionwrap>(args.This());
    User *user = pt->ptsession->GetUser();
	Local<Context> context = isolate->GetCurrentContext();
	uint32_t v = 1;
	Local<Object> objsess = Userwrap::returnobj(isolate, user, v);
    args.GetReturnValue().Set(objsess);
}

void Sessionwrap::GetWASID(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Sessionwrap* obj = ObjectWrap::Unwrap<Sessionwrap>(args.Holder());

	std::string resultat = obj->ptsession->cookies;



	args.GetReturnValue().Set(String::NewFromUtf8(isolate, resultat.c_str()));
}

void Sessionwrap::GetDirectorywrap(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Sessionwrap* obj = ObjectWrap::Unwrap<Sessionwrap>(args.Holder());
	double x = 1;
	args.GetReturnValue().Set(Number::New(isolate, x));
}

void Sessionwrap::IsValid(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Sessionwrap* obj = ObjectWrap::Unwrap<Sessionwrap>(args.Holder());
	
	
	args.GetReturnValue().Set(Boolean::New(isolate, obj->ptsession->IsValid()));
}

void Sessionwrap::LogOut(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Sessionwrap* obj = ObjectWrap::Unwrap<Sessionwrap>(args.Holder());
	obj->ptsession->LogOut();

}



}

