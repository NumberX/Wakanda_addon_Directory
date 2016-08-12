#include "Userwrap.h"
#include"GroupWrap.h"
#include"Directorywrap.h"
#include"Utility.h"
#include<string>
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
using namespace v8;

namespace WaDirectorywrap_data_v8 {

Persistent<Function> Userwrap::constructor;

Userwrap::Userwrap() : ptuser() {
}

Userwrap::~Userwrap() {
}
Local<Object> Userwrap::CreateUserWrap(Isolate* isolate, User* PtUser)
{

	EscapableHandleScope scope(isolate);

	Local<Value> argv[] = { Boolean::New(isolate, true) };
	
	Local<Context> context = isolate->GetCurrentContext();
	
	Local<Function> LocalFunction = Local<Function>::New(isolate, Userwrap::constructor);
	
	Local<Object> ObjectUserWrap = LocalFunction->NewInstance(context, 1, argv).ToLocalChecked();
	
	Userwrap* PtUserWrap = Userwrap::Unwrap<Userwrap>(ObjectUserWrap);

	PtUserWrap->ptuser = PtUser;

	return scope.Escape(ObjectUserWrap);



}

void Userwrap::Init(Local<Object> exports) {

	
  Isolate* isolate = exports->GetIsolate();

  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
 
  tpl->SetClassName(String::NewFromUtf8(isolate, "Userwrap"));
  
  tpl->InstanceTemplate()->SetInternalFieldCount(2);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetDirectorywrap", GetDirectorywrap);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetName", GetName);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "BelongsToGroupwrap_1", BelongsToGroupwrap_1);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "BelongsToGroupwrap_2", BelongsToGroupwrap_2);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsLoggedIn", IsLoggedIn);
  
  constructor.Reset(isolate, tpl->GetFunction());
  
  exports->Set(String::NewFromUtf8(isolate, "Userwrap"),
               tpl->GetFunction());
}

void Userwrap::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
  
	  
	  if (args.Length() == 0) {

		  /*
		  Traitement du cas Userwrap User=new Userwrap();
		  */

		  Userwrap* PtUserWrap = new Userwrap();

		  User *Ptuser = new User();

		  PtUserWrap->ptuser = Ptuser;

		  PtUserWrap->Wrap(args.Holder());

		  args.GetReturnValue().Set(args.Holder());
	  }
	  else if (args.Length() == 1) { 

		  /*
		  Traitement du cas Userwrap User=new Userwrap();
		  */

		  Userwrap* PtUserWrap = new Userwrap();

		  PtUserWrap->Wrap(args.Holder());

		  args.GetReturnValue().Set(args.Holder());
	  }
  } else {

  }
}



void Userwrap::GetDirectorywrap(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();

	Userwrap* obj = ObjectWrap::Unwrap<Userwrap>(args.This());

	args.GetReturnValue().Set(args.This());
}

void Userwrap::GetName(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();

	Userwrap* PtUserWrap = ObjectWrap::Unwrap<Userwrap>(args.Holder());
	
	std::string resultat = "";  
	
	PtUserWrap->ptuser->GetName(resultat);

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, resultat.c_str()));
}

void Userwrap::BelongsToGroupwrap_1(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();

	Userwrap* PtUserWrap = ObjectWrap::Unwrap<Userwrap>(args.Holder());
	
	Utility util;
	
	string inGroupName = util.V8Utf8ValueToStdString(args[0]);

	bool resultat = PtUserWrap->ptuser->BelongsToGroup(inGroupName);

	args.GetReturnValue().Set(Boolean::New(isolate, resultat));
}

void Userwrap::BelongsToGroupwrap_2(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();

	Userwrap* PtUserWrap = ObjectWrap::Unwrap<Userwrap>(args.Holder());

	Groupwrap* PtGroupWrap = ObjectWrap::Unwrap<Groupwrap>(args[0]->ToObject());
	
	bool resultat = PtUserWrap->ptuser->BelongsToGroup(PtGroupWrap->ptgroup);

	args.GetReturnValue().Set(Boolean::New(isolate, resultat));
}

void Userwrap::IsLoggedIn(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();
	
	bool resultat = false;
	
	Userwrap* PtUserWrap = ObjectWrap::Unwrap<Userwrap>(args.Holder());

	if (args[0]->IsObject())
	{
		Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args[0]->ToObject());
		resultat= PtUserWrap->ptuser->IsLoggedIn(PtSessionWrap->ptsession);
	}
	
	args.GetReturnValue().Set(Boolean::New(isolate, resultat));
}

}
