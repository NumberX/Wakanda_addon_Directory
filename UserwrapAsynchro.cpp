#include "UserwrapAsynchro.h"
#include"GroupwrapAsynchro.h"
#include"DirectorywrapAsynchro.h"
#include"ControleUser.h"
#include"ControleUserAsynchro.h"
#include"DataControle.h"
#include"Work.h"
#include"Thread_Data.h"
#include"Utility.h"
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
namespace WaDirectorywrapAsynchro_data_v8 {

Persistent<Function> UserwrapAsynchro::constructor;

UserwrapAsynchro::UserwrapAsynchro() : ptuser() {
}

Persistent<Value> UserwrapAsynchro::prototype_User_Synchrone;

Local<Boolean> UserwrapAsynchro::ControleUserUnwrap(Local<Object> handle, Isolate* isolate)
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

UserwrapAsynchro::~UserwrapAsynchro() {
}


Local<Object> UserwrapAsynchro::CreateUserWrapAsynchro(Isolate* isolate, IUser* PtUser, DirectorywrapAsynchro* PtDirectoryWrap)
{

	EscapableHandleScope scope(isolate);

	Local<Value> argv[] = { Boolean::New(isolate, true) };

	Local<Context> context = isolate->GetCurrentContext();

	Local<Function> LocalFunct = Local<Function>::New(isolate, UserwrapAsynchro::constructor);

	Local<Object> ObjectUserWrap = LocalFunct->NewInstance(context, 1, argv).ToLocalChecked();

	UserwrapAsynchro* PtUserWrap = UserwrapAsynchro::Unwrap<UserwrapAsynchro>(ObjectUserWrap);

	PtUserWrap->ptuser = PtUser;

	PtUserWrap->ptuser->Set_Directory(PtDirectoryWrap->ptdirectory);

	PtUserWrap->Pt_DirectorywrapAsynchro = PtDirectoryWrap;

	return scope.Escape(ObjectUserWrap);




}

void UserwrapAsynchro::Init(Local<Object> exports) {

	
  Isolate* isolate = exports->GetIsolate();

  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
 
  tpl->SetClassName(String::NewFromUtf8(isolate, "UserwrapAsynchro"));
  
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetDirectorywrapAsynchro", GetDirectorywrapAsynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetNameAsynchro", GetNameAsynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "BelongsToGroupwrapAsynchro", BelongsToGroupwrapAsynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsLoggedInAsynchro", IsLoggedInAsynchro);
  
  constructor.Reset(isolate, tpl->GetFunction());
  
  exports->Set(String::NewFromUtf8(isolate, "UserwrapAsynchro"),
               tpl->GetFunction());
}

void UserwrapAsynchro::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {



	  if (args.Length() == 1) {


		  UserwrapAsynchro* PtUserWrap = new UserwrapAsynchro();

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

void UserwrapAsynchro::GetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
	
	Isolate* isolate = args.GetIsolate();

	ControleUserAsynchro* PtControleUserAsynchro = new ControleUserAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleUserAsynchro->ControleGetDirectorywrapAsynchro(args, controle, Message);

	if (controle == true)
	{
		Work *work = new Work();

		work->request.data = work;

		DataControle Userdata = Pt_Vector->at(0);

		UserwrapAsynchro* PtUserWrapAsynchro = Userdata.Output.PtUserwrapAsynchro;

		ControleUser* PtControleUser = new ControleUser();

		if (PtControleUser->ControleGetPtUser(args, PtUserWrapAsynchro->ptuser, Message))
		{


			Thread_Data Pt_UserWrapAsynchro_Intra;

			Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

			work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

			Local<Function> commeback = Local<Function>::Cast(args[0]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, GetDirectorywrapAsynchroWork, GetDirectorywrapAsynchroWorkComplete);

			args.GetReturnValue().Set(Undefined(isolate));
		}

	}

	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

		args.GetReturnValue().SetNull();

	}




}

void UserwrapAsynchro::GetDirectorywrapAsynchroWork(uv_work_t  *request){
	Work *work = (Work*)(request->data);
	DirectorywrapAsynchro *pt = work->Intra_Data[0].Argument.PtUserwrapAsynchro->Pt_DirectorywrapAsynchro;


}

void UserwrapAsynchro::GetDirectorywrapAsynchroWorkComplete(uv_work_t  *request, int status){

	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);


	Work *work = (Work *)(request->data);

	DirectorywrapAsynchro *pt = work->Intra_Data[0].Argument.PtUserwrapAsynchro->Pt_DirectorywrapAsynchro;

	Local<Object> ObjectDirectoryWrap = pt->handle();

	Handle<Value> args[] = { Null(isolate), ObjectDirectoryWrap };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;
}

void UserwrapAsynchro::GetNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
	Isolate* isolate = args.GetIsolate();

	ControleUserAsynchro* PtControleUserAsynchro = new ControleUserAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleUserAsynchro->ControleGetNameAsynchro(args, controle, Message);

	if (controle == true)
	{
		Work *work = new Work();

		work->request.data = work;

		DataControle Userdata = Pt_Vector->at(0);

		UserwrapAsynchro* PtUserWrapAsynchro = Userdata.Output.PtUserwrapAsynchro;

		ControleUser* PtControleUser = new ControleUser();

		if (PtControleUser->ControleGetPtUser(args, PtUserWrapAsynchro->ptuser, Message))
		{


			Thread_Data Pt_UserWrapAsynchro_Intra;

			Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

			work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

			Local<Function> commeback = Local<Function>::Cast(args[0]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, GetNameAsynchroWork, GetNameAsynchroWorkComplete);

			args.GetReturnValue().Set(Undefined(isolate));
		}

	}

	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

		args.GetReturnValue().SetNull();

	}

}

void UserwrapAsynchro::GetNameAsynchroWork(uv_work_t  *request){

	Work *work = (Work*)(request->data);

	std::string Resultat = "";

	work->Intra_Data[0].Argument.PtUserwrapAsynchro->ptuser->GetName(Resultat);

	Thread_Data Resultat_string;

	Resultat_string.Argument.Resultat_string = new char[Resultat.length() + 1];;

	std::strcpy(Resultat_string.Argument.Resultat_string, Resultat.c_str());

	work->Intra_Data.push_back(Resultat_string);


}

void UserwrapAsynchro::GetNameAsynchroWorkComplete(uv_work_t  *request, int status){
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	char *Resultat_string = work->Intra_Data[1].Argument.Resultat_string;

	Local<String> Resultat_string_v = String::NewFromUtf8(isolate, Resultat_string);

	Handle<Value> args[] = { Null(isolate), Resultat_string_v };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}

void UserwrapAsynchro::BelongsToGroupwrapAsynchro(const FunctionCallbackInfo<Value>& args)
{

	Isolate* isolate = args.GetIsolate();

	ControleUserAsynchro* PtControleUserAsynchro = new ControleUserAsynchro();

	bool controle = false;

	std::string Message;

	int Methode = 0;

	vector<DataControle>* Pt_Vector = PtControleUserAsynchro->ControleBelongsToGroupwrapAsynchro(args, controle, Message, Methode);

	if (controle == true)
	{
		Work *work = new Work();

		work->request.data = work;

		DataControle Userdata = Pt_Vector->at(0);

		UserwrapAsynchro* PtUserWrapAsynchro = Userdata.Output.PtUserwrapAsynchro;

		Thread_Data Pt_UserWrapAsynchro_Intra;

		Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

		work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);
		if (Methode==1)
		{ 
			DataControle Groupdata = Pt_Vector->at(1);

			GroupwrapAsynchro* PtGroupWrapAsynchro = Groupdata.Output.PtGroupwrapAsynchro;

			Thread_Data Pt_GroupWrapAsynchro_Intra;

			Pt_GroupWrapAsynchro_Intra.Argument.PtGroupWrapAsynchro = PtGroupWrapAsynchro;

			work->Intra_Data.push_back(Pt_GroupWrapAsynchro_Intra);

			Local<Function> commeback = Local<Function>::Cast(args[1]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, BelongsToGroupwrap_2AsynchroWork, BelongsToGroupwrap_2AsynchroWorkComplete);

			args.GetReturnValue().Set(Undefined(isolate));
		}
		if (Methode == 2)
		{

			Thread_Data Pt_inGroupID;

			DataControle Groupdata = Pt_Vector->at(1);

			Pt_inGroupID.Argument.GroupId = Groupdata.Output.GroupId;

			work->Input_Data.push_back(Pt_inGroupID);

			Local<Function> commeback = Local<Function>::Cast(args[1]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, BelongsToGroupwrap_1AsynchroWork, BelongsToGroupwrap_1AsynchroWorkComplete);

			args.GetReturnValue().Set(Undefined(isolate));

		}

	}
  else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetUndefined();

		}
	
}

void UserwrapAsynchro::BelongsToGroupwrap_1AsynchroWork(uv_work_t  *request){
	Work *work = (Work*)(request->data);

	string GroupId = work->Input_Data[0].Argument.GroupId;

	UserwrapAsynchro* PtUserWrapAsynchro = work->Intra_Data[0].Argument.PtUserwrapAsynchro;

	Thread_Data Resultat_Intra;

    Resultat_Intra.Argument.Resultat = PtUserWrapAsynchro->ptuser->BelongsToGroup(GroupId);

	work->Intra_Data.push_back(Resultat_Intra);


}

void UserwrapAsynchro::BelongsToGroupwrap_1AsynchroWorkComplete(uv_work_t  *request, int status){

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


void UserwrapAsynchro::BelongsToGroupwrap_2AsynchroWork(uv_work_t  *request){
	Work *work = (Work*)(request->data);

	GroupwrapAsynchro* PtGroupWrapAsynchro = work->Intra_Data[1].Argument.PtGroupWrapAsynchro;

	UserwrapAsynchro* PtUserWrapAsynchro = work->Intra_Data[0].Argument.PtUserwrapAsynchro;

	Thread_Data Resultat_Intra;

	Resultat_Intra.Argument.Resultat = PtUserWrapAsynchro->ptuser->BelongsToGroup(PtGroupWrapAsynchro->ptgroup);

	work->Input_Data.push_back(Resultat_Intra);

}

void UserwrapAsynchro::BelongsToGroupwrap_2AsynchroWorkComplete(uv_work_t  *request, int status){

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

void UserwrapAsynchro::IsLoggedInAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){

	Isolate* isolate = args.GetIsolate();

	ControleUserAsynchro* PtControleUserAsynchro = new ControleUserAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleUserAsynchro->ControleIsLoggedInAsynchro(args, controle, Message);

	if (controle == true)
	{
		Work *work = new Work();

		work->request.data = work;

		DataControle Userdata = Pt_Vector->at(0);

		UserwrapAsynchro* PtUserWrapAsynchro = Userdata.Output.PtUserwrapAsynchro;

		ControleUser* PtControleUser = new ControleUser();

		if (PtControleUser->ControleGetPtUser(args, PtUserWrapAsynchro->ptuser, Message))
		{

			Thread_Data Pt_UserWrapAsynchro_Intra;

			Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

			work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

			Thread_Data Pt_SessionWrapAsynchro_Intra;

			DataControle Sessiondata = Pt_Vector->at(1);

			SessionwrapAsynchro* PtSessionWrapAsynchro = Sessiondata.Output.PtSessionwrapAsynchro;

			Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

			work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);

			Local<Function> commeback = Local<Function>::Cast(args[1]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, IsLoggedInAsynchroWork, IsLoggedInAsynchroWorkComplete);

			args.GetReturnValue().Set(Undefined(isolate));
		}
	}

	
		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetNull();
		}

}

void UserwrapAsynchro::IsLoggedInAsynchroWork(uv_work_t  *request){
	Work *work = (Work*)(request->data);
	SessionwrapAsynchro* PtSessionWrapAsynchro = work->Intra_Data[1].Argument.ptSessionwrapAsynchro;

	UserwrapAsynchro* PtUserWrapAsynchro = work->Intra_Data[0].Argument.PtUserwrapAsynchro;

	Thread_Data Resultat_Intra;
	bool Resultat;

	Resultat = PtUserWrapAsynchro->ptuser->IsLoggedIn(PtSessionWrapAsynchro->ptsession);

	Resultat_Intra.Argument.Resultat = Resultat;
	work->Input_Data.push_back(Resultat_Intra);


}

void UserwrapAsynchro::IsLoggedInAsynchroWorkComplete(uv_work_t  *request, int status){

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


}
