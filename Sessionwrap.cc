#include "Sessionwrap.h"
#include "Userwrap.h"
#include<string>
#include<iostream>
#include"Session.h"
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
using namespace WaDirectory;
using namespace std;

namespace WaDirectorywrap_data_v8 {

Persistent<Function> Sessionwrap::constructor;

Sessionwrap::Sessionwrap():ptsession()  {
	
}

Sessionwrap::~Sessionwrap() {

}
Local<Object> Sessionwrap::CreateSessionWrap(Isolate* isolate, Session* PtSession)
{
	EscapableHandleScope scope(isolate);

	Local<Value> argv[] = { Boolean::New(isolate, true) };
	
	Local<Context> context = isolate->GetCurrentContext();
	
	Local<Function> LocalFunct = Local<Function>::New(isolate, Sessionwrap::constructor);
	
	Local<Object> ObjectSessionWrap = LocalFunct->NewInstance(context, 1, argv).ToLocalChecked();
	
	Sessionwrap* PtSessionWrap = Sessionwrap::Unwrap<Sessionwrap>(ObjectSessionWrap);

	PtSessionWrap->ptsession = PtSession;

	return scope.Escape(ObjectSessionWrap);



}
void Sessionwrap::Init(Local<Object> exports) {

  Isolate* isolate = exports->GetIsolate();
  
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
		  /*Traitement du cas UserWrap PtUserWarp = new UserWrap() */
		  Sessionwrap*  PtSessionWrap= new Sessionwrap();
		  
		  Session *PtSession = new Session();
		  
		  PtSessionWrap->ptsession = PtSession;
		  
		  PtSessionWrap->Wrap(args.Holder());
		  
		  args.GetReturnValue().Set(args.Holder());
	  }
	  
	  else if (args.Length() == 1) { 
		  /*Traitement du cas UserWrap PtUserWarp = new UserWrap(User) */
		
		  Sessionwrap* PtSessionWrap = new Sessionwrap();
		  
		  PtSessionWrap->Wrap(args.This());
		  
		  args.GetReturnValue().Set(args.Holder());
	  }
  } else {
    
  }
}


void Sessionwrap::GetUserwrap(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args.This());

	User *PtUser = PtSessionWrap->ptsession->GetUser();
	
	Local<Context> context = isolate->GetCurrentContext();
	
	Local<Object> ObjectUserWrap = Userwrap::CreateUserWrap(isolate, PtUser);
    
	args.GetReturnValue().Set(ObjectUserWrap);
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

	Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args.Holder());
	
	args.GetReturnValue().Set(Boolean::New(isolate, PtSessionWrap->ptsession->IsValid()));
}

void Sessionwrap::LogOut(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();

	Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args.Holder());
	
	PtSessionWrap->ptsession->LogOut();

}



}

