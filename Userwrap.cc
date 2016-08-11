#include "Userwrap.h"
#include"Directorywrap.h"
#include<string>
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
using v8::Boolean;
using namespace v8;
Persistent<Function> Userwrap::constructor;

Userwrap::Userwrap() : ptuser() {
}

Userwrap::~Userwrap() {
}
Local<Object> Userwrap::returnobj(Isolate* isolate, User* b, uint32_t index)
{
	EscapableHandleScope scope(isolate);

	// Get a new instance of PersonWrap
	Local<Value> argv[] = { Boolean::New(isolate, true) };
	Local<Context> context = isolate->GetCurrentContext();
	Local<Function> cons = Local<Function>::New(isolate, Userwrap::constructor);
	Local<Object> obj1 = cons->NewInstance(context, 1, argv).ToLocalChecked();
	Userwrap* pw = Userwrap::Unwrap<Userwrap>(obj1);

	pw->ptuser = b;

	return scope.Escape(obj1);



}

void Userwrap::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "Userwrap"));
  tpl->InstanceTemplate()->SetInternalFieldCount(2);

  // Prototype
 

  NODE_SET_PROTOTYPE_METHOD(tpl, "plusOne", PlusOne);
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
    // Invoked as constructor: `new Userwrap(...)`
	  if (args.Length() == 0) {
		  Userwrap* pw = new Userwrap();
		  User *p = new User();
		  pw->ptuser = p;
		  pw->Wrap(args.This());
		  args.GetReturnValue().Set(args.This());
	  }
	  else if (args.Length() == 1) { // we have a Directory object allocated
		  Userwrap* pw = new Userwrap();
		  pw->Wrap(args.This());
		  args.GetReturnValue().Set(args.This());
	  }
  } else {

  }
}

void Userwrap::PlusOne(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  Userwrap* obj = ObjectWrap::Unwrap<Userwrap>(args.Holder());
  double x = 1;

  //x++;

  args.GetReturnValue().Set(Number::New(isolate, x));
}

void Userwrap::GetDirectorywrap(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Userwrap* obj = ObjectWrap::Unwrap<Userwrap>(args.This());
	


	args.GetReturnValue().Set(args.This());
}

void Userwrap::GetName(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Userwrap* obj = ObjectWrap::Unwrap<Userwrap>(args.Holder());
	
	std::string resultat = "";  obj->ptuser->GetName(resultat);

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, resultat.c_str()));
}

void Userwrap::BelongsToGroupwrap_1(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Userwrap* obj = ObjectWrap::Unwrap<Userwrap>(args.Holder());
	
	bool resultat = true;
	args.GetReturnValue().Set(Boolean::New(isolate, resultat));
}

void Userwrap::BelongsToGroupwrap_2(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	Userwrap* obj = ObjectWrap::Unwrap<Userwrap>(args.Holder());
	bool resultat = true;
	args.GetReturnValue().Set(Boolean::New(isolate, resultat));
}

void Userwrap::IsLoggedIn(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	bool resultat = false;
	Userwrap* obj = ObjectWrap::Unwrap<Userwrap>(args.Holder());
	if (args[0]->IsObject())
	{
		Sessionwrap* objsession = ObjectWrap::Unwrap<Sessionwrap>(args[0]->ToObject());
		resultat= obj->ptuser->IsLoggedIn(objsession->ptsession);
	}
	
	args.GetReturnValue().Set(Boolean::New(isolate, resultat));
}

}
