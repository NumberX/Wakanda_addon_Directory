#include "Sessionwrap.h"
#include"ControleSession.h"
#include"ControleSessionsynchro.h"
#include"DataControlesyn.h"
#include "Userwrap.h"
#include"Utility.h"
#include<string>
#include<iostream>
#include"Session.h"
#include"DirectoryWrap.h"
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
using namespace Controle;

namespace WaDirectorywrap_data_v8 {

	Persistent<Function> Sessionwrap::constructor;

	Persistent<Value> Sessionwrap::prototype_Session_Synchrone;
	
	Sessionwrap::Sessionwrap() :ptsession()  {

	}

	Sessionwrap::~Sessionwrap() {

	}

	ISession* Sessionwrap::GetSession() {
		return this->ptsession;
	}
	Local<Boolean> Sessionwrap::ControleSessionUnwrap(Local<Object> handle, Isolate* isolate)
	{
		EscapableHandleScope scope(isolate);

		if (!handle.IsEmpty() && handle->InternalFieldCount() == 1) {

			Local<Value> Pt_Prototype = handle->GetPrototype();
			Utility util;

			if (Pt_Prototype == prototype_Session_Synchrone) {
				Local<Boolean> Resultat = Boolean::New(isolate, true);
				return scope.Escape(Resultat);

			}


		}
		Local<Boolean> Resultat = Boolean::New(isolate, false);
		return scope.Escape(Resultat);
	}
	Local<Object> Sessionwrap::CreateSessionWrap(Isolate* isolate, ISession* PtSession, Directorywrap* PtDirectoryWrap)
	{
		EscapableHandleScope scope(isolate);

		Local<Value> argv[] = { Boolean::New(isolate, true) };

		Local<Context> context = isolate->GetCurrentContext();

		Local<Function> LocalFunct = Local<Function>::New(isolate, Sessionwrap::constructor);

		Local<Object> ObjectSessionWrap = LocalFunct->NewInstance(context, 1, argv).ToLocalChecked();

		Sessionwrap* PtSessionWrap = Sessionwrap::Unwrap<Sessionwrap>(ObjectSessionWrap);

		PtSessionWrap->ptsession = PtSession;

		PtSessionWrap->ptsession->Set_Directory(PtDirectoryWrap->GetDirectory());

		PtSessionWrap->Pt_DirectoryWrap = PtDirectoryWrap;

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
		
		ControleSession* ControSession = new ControleSession();

		std::string Message;
		if (args.IsConstructCall()) {

			

			 if (ControSession->ControleGetLenght(args,Message,1 )) {
				

				Sessionwrap* PtSessionWrap = new Sessionwrap();

				PtSessionWrap->Wrap(args.This());

				prototype_Session_Synchrone.Reset(isolate, args.This()->GetPrototype());

				args.GetReturnValue().Set(args.Holder());
			}
			 else
			 {

				 isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

				 args.GetReturnValue().SetUndefined();

			 }
		}
		else {

			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "To create a object of Session you need to pass from Directory object ")));

			args.GetReturnValue().SetUndefined();
		}
	}


	void Sessionwrap::GetUserwrap(const FunctionCallbackInfo<Value>& args) {

		Isolate* isolate = args.GetIsolate();


		if (ControleSessionUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this> is not a Group object")));

			args.GetReturnValue().SetUndefined();
		}
		else{
			Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args.Holder());
			string Message = "";
			ControleSession PtcontroleSession;
			if (PtcontroleSession.ControlePtSession(PtSessionWrap->ptsession, Message) == true)
			{
				if (PtSessionWrap->ptsession->IsValid())
				{ 
				IUser *PtUser = PtSessionWrap->ptsession->GetUser();

				Local<Context> context = isolate->GetCurrentContext();


				Local<Object> ObjectUserWrap = Userwrap::CreateUserWrap(isolate, PtUser, PtSessionWrap->Pt_DirectoryWrap);

				args.GetReturnValue().Set(ObjectUserWrap);
				}
				else
				{
					args.GetReturnValue().SetNull();

				}
			}
			else
			{
				isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

				args.GetReturnValue().SetUndefined();
			}
		}
	}

	void Sessionwrap::GetWASID(const FunctionCallbackInfo<Value>& args) {

		Isolate* isolate = args.GetIsolate();

		if (ControleSessionUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a Group object")));

			args.GetReturnValue().SetUndefined();
		}
		else{
			Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args.Holder());

			string Message = "";

			ControleSession PtcontroleSession;
			if (PtcontroleSession.ControlePtSession(PtSessionWrap->ptsession, Message) == true)
			{
				std::string resultat = PtSessionWrap->ptsession->cookies;

				args.GetReturnValue().Set(String::NewFromUtf8(isolate, resultat.c_str()));
			}
			else
			{
				isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

				args.GetReturnValue().SetNull();
			}
		}
	}

	void Sessionwrap::GetDirectorywrap(const FunctionCallbackInfo<Value>& args) {

		Isolate* isolate = args.GetIsolate();

		if (ControleSessionUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a Group object")));

			args.GetReturnValue().SetNull();
		}
		else{
			Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args.Holder());

			Local<Object> ObjectDirectoryWrap = PtSessionWrap->Pt_DirectoryWrap->handle();
			
			args.GetReturnValue().Set(ObjectDirectoryWrap);


		}
	}

	void Sessionwrap::IsValid(const FunctionCallbackInfo<Value>& args) {

		Isolate* isolate = args.GetIsolate();

		if (ControleSessionUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a Session object")));

			args.GetReturnValue().SetUndefined();
		}
		else{
			Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args.Holder());

			string Message = "";

			ControleSession PtcontroleSession;
			if (PtcontroleSession.ControlePtSession(PtSessionWrap->ptsession, Message) == true)
			{
				args.GetReturnValue().Set(Boolean::New(isolate, PtSessionWrap->ptsession->IsValid()));
			}
			else
			{
				isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

				args.GetReturnValue().SetNull();
			}
		}
	}

	void Sessionwrap::LogOut(const FunctionCallbackInfo<Value>& args) {

		Isolate* isolate = args.GetIsolate();

		if (ControleSessionUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a Session object")));

			args.GetReturnValue().SetUndefined();
		}
		else{
			Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args.Holder());

			string Message = "";

			ControleSession PtcontroleSession;
			if (PtcontroleSession.ControlePtSession(PtSessionWrap->ptsession, Message) == true)
			{

				PtSessionWrap->ptsession->LogOut();
				PtSessionWrap->ptsession->cookies = "";
	
				args.GetReturnValue().SetUndefined();
			}
			else
			{
				isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

				args.GetReturnValue().SetNull();
			}
		}
	}



}
