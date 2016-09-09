#include "Userwrap.h"
#include"GroupWrap.h"
#include"Directorywrap.h"
#include"Utility.h"
#include"Work.h"
#include"Thread_Data.h"
#include"ControleUsersynchro.h"
#include"DataControlesyn.h"
#include<string>
#include<iostream>
#include"v8.h"
using namespace v8;
using namespace std;
using namespace WaDirectory_Controle;
namespace WaDirectory_View {

Persistent<Function> Userwrap::constructor;

Persistent<Value> Userwrap::prototype_User_Synchrone;

Local<Boolean> Userwrap::ControleUserUnwrap(Local<Object> handle, Isolate* isolate)
{
	EscapableHandleScope scope(isolate);

	if (!handle.IsEmpty() && handle->InternalFieldCount() == 1) {

		Local<Value> Pt_Prototype = handle->GetPrototype();
		
		Tools::Utility util;

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

	Local<v8::Object> ObjectInvoke = Object::New(isolate);

	Local<Boolean> Invoke = Boolean::New(isolate, true);

	ObjectInvoke->Set(String::NewFromUtf8(isolate, "Invoke"), Invoke);

	Local<Value> argv[] = { Boolean::New(isolate, true), ObjectInvoke };

	Local<Context> context = isolate->GetCurrentContext();

	Local<Function> LocalFunct = Local<Function>::New(isolate, Userwrap::constructor);

	Local<Object> ObjectUserWrap = LocalFunct->NewInstance(context, 2, argv).ToLocalChecked();

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

			Local<Object> InvokeObject = args[1]->ToObject();

			Local<String> InvokeName = String::NewFromUtf8(isolate, "Invoke");

			if (InvokeObject->Get(InvokeName)->IsBoolean())
			{
				if (InvokeObject->Get(InvokeName)->ToBoolean()->IsTrue())
				{

					Userwrap* PtUserWrap = new Userwrap();

					PtUserWrap->Wrap(args.This());

					prototype_User_Synchrone.Reset(isolate, args.This()->GetPrototype());

					args.GetReturnValue().Set(args.This());
				}
			}
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
void Userwrap::BelongsToGroupwrapWork1(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);

	string GroupId = work->Input_Data[0].Argument.GroupId;

	Userwrap* PtUserWrap = work->Intra_Data[0].Argument.PtUserwrap;

	Thread_Data Resultat_Intra;

	Resultat_Intra.Argument.Resultat = PtUserWrap->ptuser->BelongsToGroup(GroupId);

	work->Intra_Data.push_back(Resultat_Intra);
}
void Userwrap::BelongsToGroupwrapWorkComplete1(uv_work_t  *request, int status)
{
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	bool Resultat = work->Intra_Data[0].Argument.Resultat;

	Local<Boolean> Resultat_v8 = Boolean::New(isolate, Resultat);

	Handle<Value> args[] = { Null(isolate), Resultat_v8 };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;
}
void Userwrap::BelongsToGroupwrapWork2(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);

	Groupwrap* PtGroupWrap = work->Intra_Data[1].Argument.PtGroupWrap;

	Userwrap* PtUserWrap = work->Intra_Data[0].Argument.PtUserwrap;

	Thread_Data Resultat_Intra;

	Resultat_Intra.Argument.Resultat = PtUserWrap->ptuser->BelongsToGroup(PtGroupWrap->ptgroup);

	work->Input_Data.push_back(Resultat_Intra);

}
void Userwrap::BelongsToGroupwrapWorkComplete2(uv_work_t  *request, int status)
{
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	bool Resultat = work->Input_Data[0].Argument.Resultat;

	Local<Boolean> Resultat_v8 = Boolean::New(isolate, Resultat);

	Handle<Value> args[] = { Null(isolate), Resultat_v8 };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

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

		Work *work = new Work();

		work->request.data = work;

		DataControlesyn Userdata = Pt_Vector->at(0);

		Userwrap* PtUserWrap = Userdata.Output.PtUserwrap;

		Thread_Data Pt_UserWrap_Intra;

		Pt_UserWrap_Intra.Argument.PtUserwrap = PtUserWrap;

		work->Intra_Data.push_back(Pt_UserWrap_Intra);
		if (Methode == 1)
		{
			DataControlesyn Groupdata = Pt_Vector->at(1);

			Groupwrap* PtGroupWrap = Groupdata.Output.PtGroupwrap;

			Thread_Data Pt_GroupWrapAsynchro_Intra;

			Pt_GroupWrapAsynchro_Intra.Argument.PtGroupWrap = PtGroupWrap;

			work->Intra_Data.push_back(Pt_GroupWrapAsynchro_Intra);

			Local<Function> commeback = Local<Function>::Cast(args[1]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, BelongsToGroupwrapWork2, BelongsToGroupwrapWorkComplete2);

			args.GetReturnValue().Set(Undefined(isolate));
		}
		if (Methode == 2)
		{

			Thread_Data Pt_inGroupID;

			DataControlesyn Groupdata = Pt_Vector->at(1);

			Pt_inGroupID.Argument.GroupId = Groupdata.Output.GroupId;

			work->Input_Data.push_back(Pt_inGroupID);

			Local<Function> commeback = Local<Function>::Cast(args[1]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, BelongsToGroupwrapWork1, BelongsToGroupwrapWorkComplete1);

			args.GetReturnValue().Set(Undefined(isolate));

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
		Work *work = new Work();

		work->request.data = work;

		DataControlesyn Userdata = Pt_Vector->at(0);

		Userwrap* PtUserWrap = Userdata.Output.PtUserwrap;

		Thread_Data Pt_UserWrap_Intra;

		Pt_UserWrap_Intra.Argument.PtUserwrap = PtUserWrap;

		work->Intra_Data.push_back(Pt_UserWrap_Intra);

		Thread_Data Pt_SessionWrap_Intra;

		DataControlesyn Sessiondata = Pt_Vector->at(1);

		Sessionwrap* PtSessionWrap = Sessiondata.Output.PtSessionwrap;

		Pt_SessionWrap_Intra.Argument.ptSessionwrap = PtSessionWrap;

		work->Intra_Data.push_back(Pt_SessionWrap_Intra);

		Local<Function> commeback = Local<Function>::Cast(args[1]);

		work->callback.Reset(isolate, commeback);

		uv_queue_work(uv_default_loop(), &work->request, IsLoggedInWork, IsLoggedInWorkComplete);

		args.GetReturnValue().Set(Undefined(isolate));
		
	}

	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

		args.GetReturnValue().SetNull();

	}
	args.GetReturnValue().Set(Boolean::New(isolate, resultat));

}
void Userwrap::IsLoggedInWork(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);
	Sessionwrap* PtSessionWrap = work->Intra_Data[1].Argument.ptSessionwrap;

	Userwrap* PtUserWrap = work->Intra_Data[0].Argument.PtUserwrap;

	Thread_Data Resultat_Intra;
	bool Resultat;

	Resultat = PtUserWrap->ptuser->IsLoggedIn(PtSessionWrap->ptsession);

	Resultat_Intra.Argument.Resultat = Resultat;
	work->Input_Data.push_back(Resultat_Intra);
}


void Userwrap::IsLoggedInWorkComplete(uv_work_t  *request, int status)
{
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	bool Resultat = work->Input_Data[0].Argument.Resultat;

	Local<Boolean> Resultat_v8 = Boolean::New(isolate, Resultat);

	Handle<Value> args[] = { Null(isolate), Resultat_v8 };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;
}

IUser* Userwrap::GetUserData()
{
	return this->ptuser;
}
}
