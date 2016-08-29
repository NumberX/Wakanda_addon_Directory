#include "Userwrap.h"
#include"GroupWrap.h"
#include"Directorywrap.h"
#include"Utility.h"
#include"ControleUser.h"
#include<string>
#include<iostream>
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
using namespace Controle;
using namespace std;

namespace WaDirectorywrap_data_v8 {

Persistent<Function> Userwrap::constructor;

Persistent<Value> Userwrap::prototype_User_Synchrone;

Local<Boolean> Userwrap::ControleUserUnwrap(Local<Object> handle, Isolate* isolate)
{
	EscapableHandleScope scope(isolate);

	if (!handle.IsEmpty() && handle->InternalFieldCount() == 1) {

		Local<Value> Pt_Prototype = handle->GetPrototype();
		Utility util;

		if (Pt_Prototype == prototype_User_Synchrone) {
			Local<Boolean> Resultat = Boolean::New(isolate, true);
			return scope.Escape(Resultat);

		}


	}
	Local<Boolean> Resultat = Boolean::New(isolate, false);
	return scope.Escape(Resultat);
}
Userwrap::Userwrap() : ptuser() {
}


Userwrap::~Userwrap() {
}
Local<Object> Userwrap::CreateUserWrap(Isolate* isolate, User* PtUser,Directorywrap* PtDirectoryWrap)
{

	EscapableHandleScope scope(isolate);

	Local<Value> argv[] = { Boolean::New(isolate, true) };

	Local<Context> context = isolate->GetCurrentContext();

	Local<Function> LocalFunct = Local<Function>::New(isolate, Userwrap::constructor);

	Local<Object> ObjectUserWrap = LocalFunct->NewInstance(context, 1, argv).ToLocalChecked();

	Userwrap* PtUserWrap = Userwrap::Unwrap<Userwrap>(ObjectUserWrap);

	PtUserWrap->ptuser = PtUser;

	PtUserWrap->ptuser->Set_Directory(PtDirectoryWrap->GetDirectory());

	PtUserWrap->Pt_DirectoryWrap = PtDirectoryWrap;


	return scope.Escape(ObjectUserWrap);




}

void Userwrap::Init(Local<Object> exports) {

	
  Isolate* isolate = exports->GetIsolate();

  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
 
  tpl->SetClassName(String::NewFromUtf8(isolate, "Userwrap"));
  
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetDirectorywrap", GetDirectorywrap);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetName", GetName);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "BelongsToGroupwrap", BelongsToGroupwrap);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsLoggedIn", IsLoggedIn);
  
  constructor.Reset(isolate, tpl->GetFunction());
  
  exports->Set(String::NewFromUtf8(isolate, "Userwrap"),
               tpl->GetFunction());
}

void Userwrap::New(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	if (args.IsConstructCall()) {



		if (args.Length() == 1) {


			Userwrap* PtUserWrap = new Userwrap();

			PtUserWrap->Wrap(args.This());

			prototype_User_Synchrone.Reset(isolate, args.This()->GetPrototype());

			args.GetReturnValue().Set(args.This());
		}
		else
		{

			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "To create a object of User you need to pass from Directory object ")));

			args.GetReturnValue().SetUndefined();

		}
	}
	else {

		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "To create a object of User  you need to pass from Directory object ")));

		args.GetReturnValue().SetUndefined();
	}
}



void Userwrap::GetDirectorywrap(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	if (ControleUserUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a User object")));

		args.GetReturnValue().SetNull();
	}
	else{
		Userwrap* PtUserwrap = ObjectWrap::Unwrap<Userwrap>(args.Holder());

		Local<Object> ObjectDirectoryWrap = PtUserwrap->Pt_DirectoryWrap->handle();

		args.GetReturnValue().Set(ObjectDirectoryWrap);


	}
}

void Userwrap::GetName(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();


	if (ControleUserUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a User object")));

		args.GetReturnValue().SetNull();
	}
	else{
		Userwrap* PtUserWrap = ObjectWrap::Unwrap<Userwrap>(args.Holder());

		std::string resultat = "";
		
		std::string Message;

		ControleUser* PtControleUser = new ControleUser();

		if (PtControleUser->ControleGetPtUser(args,PtUserWrap->ptuser,Message))
		{ 
		PtUserWrap->ptuser->GetName(resultat);

		std::string res = PtUserWrap->ptuser->Username;

		args.GetReturnValue().Set(String::NewFromUtf8(isolate, res.c_str()));
		}
		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetNull();

		}
	}
}


void Userwrap::BelongsToGroupwrap(const FunctionCallbackInfo<Value>& args) 
{

	Isolate* isolate = args.GetIsolate();

	bool resultat = false;

	ControleUser* PtControleUser = new ControleUser();
	std::string Message;

	if (ControleUserUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a User object")));

		args.GetReturnValue().SetNull();
	}
	else{
		Userwrap* PtUserWrap = ObjectWrap::Unwrap<Userwrap>(args.Holder());
		if (PtControleUser->ControleGetLenght(args,Message,1))
		{ 
		if (Groupwrap::ControleGroupUnwrap(args[0]->ToObject(), isolate)->BooleanValue() == true)
		{

			Groupwrap* PtGroupWrap = ObjectWrap::Unwrap<Groupwrap>(args[0]->ToObject());
			
			resultat = PtUserWrap->ptuser->BelongsToGroup(PtGroupWrap->ptgroup);

			args.GetReturnValue().Set(Boolean::New(isolate, resultat));
		}
		else
		{
			if (PtControleUser->ControleGetType(args, Message, 0))
			{
				Utility util;
				
				string Idgroup = util.V8Utf8ValueToStdString(args[0]);

				bool resultat1 ;resultat1 = PtUserWrap->ptuser->BelongsToGroup(Idgroup);
			
				args.GetReturnValue().Set(Boolean::New(isolate, resultat1));

			}
			else
			{ 
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetNull();
			}
		}


		}
		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetUndefined();

		}
	}
}



void Userwrap::IsLoggedIn(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();
	
	bool resultat = false;

	if (ControleUserUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this> is not a User object")));

		args.GetReturnValue().SetUndefined();
	}
	else{
		Userwrap* PtUserWrap = ObjectWrap::Unwrap<Userwrap>(args.Holder());
		if (Sessionwrap::ControleSessionUnwrap(args[0]->ToObject(), isolate)->BooleanValue() == true)
		{

				Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args[0]->ToObject());
				if (PtSessionWrap->ptsession->IsValid())
				resultat = PtUserWrap->ptuser->IsLoggedIn(PtSessionWrap->ptsession);

		}
		else
		{
			//isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong Session argument ")));

			args.GetReturnValue().Set(Boolean::New(isolate, resultat));
			//args.GetReturnValue().SetNull();
		}

		args.GetReturnValue().Set(Boolean::New(isolate, resultat));
	}
}

}
