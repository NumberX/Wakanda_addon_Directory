#include "Groupwrap.h"
#include"ControleGroup.h"
#include"Directorywrap.h"
#include"ControleGroupsynchro.h"
#include"DataControlesyn.h"
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
using namespace Controle;
namespace WaDirectorywrap_data_v8 {

Persistent<Function> Groupwrap::constructor;

Persistent<Value> Groupwrap::prototype_Group_Synchrone;

Local<Boolean> Groupwrap::ControleGroupUnwrap(Local<Object> handle, Isolate* isolate)
{
	EscapableHandleScope scope(isolate);

	if (!handle.IsEmpty() && handle->InternalFieldCount() == 1) {

		Local<Value> Pt_Prototype = handle->GetPrototype();
		Utility util;

		if (Pt_Prototype == prototype_Group_Synchrone) {
			Local<Boolean> Resultat = Boolean::New(isolate, true);
			return scope.Escape(Resultat);

		}


	}
	Local<Boolean> Resultat = Boolean::New(isolate, false);
	return scope.Escape(Resultat);
}

Groupwrap::Groupwrap() : ptgroup() {
}


Groupwrap::~Groupwrap() {
}

Local<Object> Groupwrap::CreateGroupWrap(Isolate* isolate, IGroup* PtGroup,Directorywrap* PtDirectoryWrap)
{

	EscapableHandleScope scope(isolate);

	Local<Value> argv[] = { Boolean::New(isolate, true) };
	
	Local<Context> context = isolate->GetCurrentContext();
	
	Local<Function> LocalFunction = Local<Function>::New(isolate, Groupwrap::constructor);
	
	Local<Object> ObjectGroupWrap = LocalFunction->NewInstance(context, 1, argv).ToLocalChecked();
	
	Groupwrap* PtGroupWrap = Groupwrap::Unwrap<Groupwrap>(ObjectGroupWrap);

	PtGroupWrap->ptgroup = PtGroup;

	PtGroupWrap->Pt_DirectoryWrap = PtDirectoryWrap;

	PtGroupWrap->ptgroup->Set_Directory(PtGroupWrap->Pt_DirectoryWrap->GetDirectory());

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



		if (args.Length() == 1) {


			Groupwrap* PtGroupWrap = new Groupwrap();

			PtGroupWrap->Wrap(args.This());

			prototype_Group_Synchrone.Reset(isolate, args.This()->GetPrototype());

			args.GetReturnValue().Set(args.Holder());
		}
		else
		{

			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "To create a object of Group you need to pass from Directory object ")));

			args.GetReturnValue().SetUndefined();

		}
	}
	else {

		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "To create a object of Group  you need to pass from Directory object ")));

		args.GetReturnValue().SetUndefined();
	}
}


void Groupwrap::GetName(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	ControleGroupsynchro* PtControleGroupsynchro = new ControleGroupsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleGroupsynchro->ControleGetNamesynchro(args, controle, Message);

	if (controle == true)
	{
		std::string resultat = "";

		DataControlesyn Groupdata = Pt_Vector->at(0);

		Groupwrap* PtGroupWrap = Groupdata.Output.PtGroupwrap;

		PtGroupWrap->ptgroup->GetName(resultat);

		args.GetReturnValue().Set(String::NewFromUtf8(isolate, resultat.c_str()));
	}
else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetNull();
		}
		
	
}
void Groupwrap::GetUserwrapByName(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();

	ControleGroupsynchro* PtControleGroupsynchro = new ControleGroupsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleGroupsynchro->ControleGetUserwrapByNamesynchro(args, controle, Message);

	if (controle == true)
	{
		std::string resultat = "";

		DataControlesyn Groupdata = Pt_Vector->at(0);

		Groupwrap* PtGroupWrap = Groupdata.Output.PtGroupwrap;

		Utility util;

		IUser *PtUser = NULL;

		DataControlesyn UserIddata = Pt_Vector->at(1);

		string  user = UserIddata.Output.UserId;

		DataControlesyn Passworddata = Pt_Vector->at(2);

		string  Password = Passworddata.Output.Password;

		PtUser = PtGroupWrap->ptgroup->GetUserByName(user, Password);

		if (PtUser)
		{

			Local<Object> PtUserWrap = Userwrap::CreateUserWrap(isolate, PtUser, PtGroupWrap->Pt_DirectoryWrap);

			args.GetReturnValue().Set(PtUserWrap);
		}
		else
		{
			args.GetReturnValue().SetNull();
		}
	}
	
	else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetNull();

		}
	
}
void Groupwrap::GetSubGroupwrapName(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();


	ControleGroupsynchro* PtControleGroupsynchro = new ControleGroupsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleGroupsynchro->ControleGetSubGroupwrapNamesynchro(args, controle, Message);

	if (controle == true)
	{
		std::vector<std::string> resultat;

		DataControlesyn Groupdata = Pt_Vector->at(0);

		Groupwrap* PtGroupWrap = Groupdata.Output.PtGroupwrap;

		PtGroupWrap->ptgroup->GetSubGroupName(resultat);

		Utility util;

		Local<Array> result_list = util.StdVectorToV8Array(isolate, resultat);

		args.GetReturnValue().Set(result_list);
	}
else
	{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetNull();
		}
	
}
void Groupwrap::GetDirectorywrap(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();


	ControleGroupsynchro* PtControleGroupsynchro = new ControleGroupsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleGroupsynchro->ControleGetNamesynchro(args, controle, Message);

	if (controle == true)
	{

		DataControlesyn Groupdata = Pt_Vector->at(0);

		Groupwrap* PtGroupWrap = Groupdata.Output.PtGroupwrap;

		Local<Object> ObjectDirectoryWrap = PtGroupWrap->Pt_DirectoryWrap->handle();;

		args.GetReturnValue().Set(ObjectDirectoryWrap);
	}

	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

		args.GetReturnValue().SetNull();
	}

}


} 