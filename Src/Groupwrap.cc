#include "Groupwrap.h"
#include"Directorywrap.h"
#include"ControleGroupsynchro.h"
#include"DataControlesyn.h"
#include"Utility.h"
#include<string>
#include<vector>
#include"Group.h"
#include"Userwrap.h"
#include<iostream>
#include"v8.h"

using namespace v8;
using namespace std;
using namespace WaDirectory_Controle;
using namespace WaDirectory_Data;
namespace WaDirectory_View {

Persistent<Function> Groupwrap::constructor;

Persistent<Value> Groupwrap::prototype_Group_Synchrone;

Local<Boolean> Groupwrap::ControleGroupUnwrap(Local<Object> handle, Isolate* isolate)
{
	EscapableHandleScope scope(isolate);

	if (!handle.IsEmpty() && handle->InternalFieldCount() == 1) {

		Local<Value> Pt_Prototype = handle->GetPrototype();
		
		Tools::Utility util;

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
IGroup* Groupwrap::GetGroupData()
{

	return this->ptgroup;
}
Local<Object> Groupwrap::CreateGroupWrap(Isolate* isolate, IGroup* PtGroup,Directorywrap* PtDirectoryWrap)
{

	EscapableHandleScope scope(isolate);
	
	Local<v8::Object> ObjectInvoke = Object::New(isolate);

	Local<Boolean> Invoke = Boolean::New(isolate, true);

	ObjectInvoke->Set(String::NewFromUtf8(isolate, "Invoke"), Invoke);

	Local<Value> argv[] = { Boolean::New(isolate, true), ObjectInvoke };
	
	Local<Context> context = isolate->GetCurrentContext();
	
	Local<Function> LocalFunction = Local<Function>::New(isolate, Groupwrap::constructor);
	
	Local<Object> ObjectGroupWrap = LocalFunction->NewInstance(context, 2, argv).ToLocalChecked();
	
	Groupwrap* PtGroupWrap = Groupwrap::Unwrap<Groupwrap>(ObjectGroupWrap);

	PtGroupWrap->ptgroup = PtGroup;

	PtGroupWrap->Pt_DirectoryWrap = PtDirectoryWrap;

	PtGroupWrap->ptgroup->Set_Directory(PtGroupWrap->Pt_DirectoryWrap->GetDirectory());

	return scope.Escape(ObjectGroupWrap);



}
void Groupwrap::Init(Local<Object> exports) {

  Isolate* isolate = exports->GetIsolate();

  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  
  tpl->SetClassName(String::NewFromUtf8(isolate, "Group"));
  
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(tpl, "GetName", GetName);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetUserByName", GetUserwrapByName);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetSubGroupsName", GetSubGroupwrapName);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetDirectory", GetDirectorywrap);

  constructor.Reset(isolate, tpl->GetFunction());

  exports->Set(String::NewFromUtf8(isolate, "Group"),
	  tpl->GetFunction());
}

void Groupwrap::New(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	ControleGroupsynchro* PtControleGroupsynchro = new ControleGroupsynchro();



	if (PtControleGroupsynchro->ControleNew(args))
	{
		
		Groupwrap* PtGroupWrap = new Groupwrap();

		PtGroupWrap->Wrap(args.This());

		prototype_Group_Synchrone.Reset(isolate, args.This()->GetPrototype());

		args.GetReturnValue().Set(args.Holder());
			
		
	}
	
	
	else {

		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "To create a object of Group  you need to pass from Directory object ")));

		args.GetReturnValue().SetUndefined();
	}

	delete PtControleGroupsynchro;
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
		
	delete PtControleGroupsynchro;
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

		Tools::Utility util;

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
	delete PtControleGroupsynchro;
	
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

		Tools::Utility util;

		Local<Array> result_list = util.StdVectorToV8Array(isolate, resultat);

		args.GetReturnValue().Set(result_list);
	}
else
	{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetNull();
		}
	delete PtControleGroupsynchro;
	
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

	delete PtControleGroupsynchro;

}


} 