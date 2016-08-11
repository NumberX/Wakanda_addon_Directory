#include "Groupwrap.h"
#include<string>
#include<vector>
#include"Group.h"
#include"Userwrap.h"
#include<iostream>
using namespace std;
using namespace WaDirectory;
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


using namespace v8;
Persistent<Function> Groupwrap::constructor;

Groupwrap::Groupwrap() : ptgroup() {
}

Groupwrap::~Groupwrap() {
}
Local<Object> Groupwrap::returnobj(Isolate* isolate, Group* b, uint32_t index)
{
	EscapableHandleScope scope(isolate);

	// Get a new instance of PersonWrap
	Local<Value> argv[] = { Boolean::New(isolate, true) };
	Local<Context> context = isolate->GetCurrentContext();
	Local<Function> cons = Local<Function>::New(isolate, Groupwrap::constructor);
	Local<Object> obj = cons->NewInstance(context, 1, argv).ToLocalChecked();
	Groupwrap* pw = Groupwrap::Unwrap<Groupwrap>(obj);

	pw->ptgroup = b;

	return scope.Escape(obj);



}
void Groupwrap::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "Groupwrap"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "plusOne", PlusOne);
 

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
		  Groupwrap* pw = new Groupwrap();
		  Group *p = new Group();
		  pw->ptgroup = p;
		  pw->Wrap(args.This());
		  args.GetReturnValue().Set(args.This());
	  }
	  else if (args.Length() == 1) { // we have a Directory object allocated
		  Groupwrap* pw = new Groupwrap();
		  pw->Wrap(args.This());
		  args.GetReturnValue().Set(args.This());
	  }
  } else {
 
  }
}

void Groupwrap::PlusOne(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  Groupwrap* obj = ObjectWrap::Unwrap<Groupwrap>(args.Holder());
  double x = 2;

  args.GetReturnValue().Set(Number::New(isolate, x));
}
void Groupwrap::GetName(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Groupwrap* obj = ObjectWrap::Unwrap<Groupwrap>(args.Holder());
	
	std::string resultat = ""; obj->ptgroup->GetName(resultat);

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, resultat.c_str()));
}
void Groupwrap::GetUserwrapByName(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	std::string res;
	Groupwrap* obj = ObjectWrap::Unwrap<Groupwrap>(args.Holder());
	String::Utf8Value userv8(args[0]);
	
	 string  user(*userv8);
	User *s = obj->ptgroup->GetUserByName(user);
	uint32_t v = 1;
	Local<Object> objsess = Userwrap::returnobj(isolate, s, v);

	args.GetReturnValue().Set(objsess);
}
void Groupwrap::GetSubGroupwrapName(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Groupwrap* obj = ObjectWrap::Unwrap<Groupwrap>(args.Holder());
	
	std::vector<std::string> resultat; obj->ptgroup->GetSubGroupName(resultat);
    Local<Array> result_list = Array::New(isolate);
	for (unsigned int i = 0; i < resultat.size(); i++) {
		Local<String> result = String::NewFromUtf8(isolate, resultat[i].c_str());

		result_list->Set(i, result);
	}
	args.GetReturnValue().Set(result_list);

}
void Groupwrap::GetDirectorywrap(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Groupwrap* obj = ObjectWrap::Unwrap<Groupwrap>(args.Holder());
	double x;
	args.GetReturnValue().Set(Number::New(isolate, x));
}

} 