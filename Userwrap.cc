#include "Userwrap.h"
#include"GroupWrap.h"
#include"Directorywrap.h"
#include"Utility.h"
#include"ControleUser.h"
#include"ControleUsersynchro.h"
#include"DataControlesyn.h"
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
Local<Object> Userwrap::CreateUserWrap(Isolate* isolate, IUser* PtUser,Directorywrap* PtDirectoryWrap)
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


	ControleUsersynchro *PtControleUsersynchro = new ControleUsersynchro();

	bool Controle = false;

	string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleUsersynchro->ControleGetDirectorywrapsynchro(args, Controle, Message);

	if (Controle == true)
	{

		DataControlesyn dataUser = Pt_Vector->at(0);

		Userwrap* PtUserWrap = dataUser.Output.PtUserwrap;

		Local<Object> ObjectDirectoryWrap = PtUserWrap->Pt_DirectoryWrap->handle();

		args.GetReturnValue().Set(ObjectDirectoryWrap);
	}
	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

		args.GetReturnValue().SetNull();

	}

}

void Userwrap::GetName(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();

	ControleUsersynchro *PtControleUsersynchro = new ControleUsersynchro();

	bool Controle = false;

	string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleUsersynchro->ControleGetNamesynchro(args, Controle, Message);

	if (Controle == true)
	{
		std::string resultat = "";

		DataControlesyn dataUser = Pt_Vector->at(0);

		Userwrap* PtUserWrap = dataUser.Output.PtUserwrap;

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


void Userwrap::BelongsToGroupwrap(const FunctionCallbackInfo<Value>& args) 
{

	Isolate* isolate = args.GetIsolate();

	bool resultat = false;

	ControleUsersynchro *PtControleUsersynchro = new ControleUsersynchro();

	bool Controle = false;

	string Message;

	int Methode = 0;

	vector<DataControlesyn>* Pt_Vector = PtControleUsersynchro->ControleBelongsToGroupwrapsynchro(args, Controle, Message,Methode);

	if (Controle == true)
	{

		DataControlesyn dataUser = Pt_Vector->at(0);

		Userwrap* PtUserWrap = dataUser.Output.PtUserwrap;
		if (Methode == 1)
		{
			DataControlesyn dataGroup = Pt_Vector->at(1);

			Groupwrap* PtGroupWrap = dataGroup.Output.PtGroupwrap;

			resultat = PtUserWrap->ptuser->BelongsToGroup(PtGroupWrap->ptgroup);

			args.GetReturnValue().Set(Boolean::New(isolate, resultat));
		}
		if (Methode == 2)
		{
			DataControlesyn dataGroup = Pt_Vector->at(1);

			string Idgroup = dataGroup.Output.GroupId;

			bool resultat1; 
			
			resultat1 = PtUserWrap->ptuser->BelongsToGroup(Idgroup);

			args.GetReturnValue().Set(Boolean::New(isolate, resultat1));

		}
	}
else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetUndefined();

		}
	
}



void Userwrap::IsLoggedIn(const FunctionCallbackInfo<Value>& args) {


	bool resultat = false;

	Isolate* isolate = args.GetIsolate();

	ControleUsersynchro *PtControleUsersynchro = new ControleUsersynchro();

	bool Controle = false;

	string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleUsersynchro->ControleIsLoggedInsynchro(args, Controle, Message);

	if (Controle == true)
	{

		DataControlesyn dataUser = Pt_Vector->at(0);

		Userwrap* PtUserWrap = dataUser.Output.PtUserwrap;

		DataControlesyn datasession = Pt_Vector->at(1);

		Sessionwrap* PtSessionWrap = datasession.Output.PtSessionwrap;

		if (PtSessionWrap->ptsession->IsValid())
			resultat = PtUserWrap->ptuser->IsLoggedIn(PtSessionWrap->ptsession);
	}

	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

		args.GetReturnValue().SetNull();

	}
	args.GetReturnValue().Set(Boolean::New(isolate, resultat));

}


}
