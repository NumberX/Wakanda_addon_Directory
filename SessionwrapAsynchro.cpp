#include "SessionwrapAsynchro.h"
#include "UserwrapAsynchro.h"
#include"GroupwrapAsynchro.h"
#include"DirectorywrapAsynchro.h"
#include"ControleSession.h"
#include"ControleSessionAsynchro.h"
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

Persistent<Value> SessionwrapAsynchro::prototype_Session_Synchrone;

Persistent<Function> SessionwrapAsynchro::constructor;

Local<Boolean> SessionwrapAsynchro::ControleSessionUnwrap(Local<Object> handle, Isolate* isolate)
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

SessionwrapAsynchro::SessionwrapAsynchro():ptsession()  {
	
}

SessionwrapAsynchro::~SessionwrapAsynchro() {

}
Local<Object> SessionwrapAsynchro::CreateSessionwrapAsynchro(Isolate* isolate, ISession* PtSession, DirectorywrapAsynchro* PtDirectoryWrap)
{
	EscapableHandleScope scope(isolate);

	Local<Value> argv[] = { Boolean::New(isolate, true) };

	Local<Context> context = isolate->GetCurrentContext();

	Local<Function> LocalFunct = Local<Function>::New(isolate, SessionwrapAsynchro::constructor);

	Local<Object> ObjectSessionWrap = LocalFunct->NewInstance(context, 1, argv).ToLocalChecked();

	SessionwrapAsynchro* PtSessionWrap = SessionwrapAsynchro::Unwrap<SessionwrapAsynchro>(ObjectSessionWrap);

	PtSessionWrap->ptsession = PtSession; 

	PtSessionWrap->ptsession->Set_Directory(PtDirectoryWrap->ptdirectory);

	PtSessionWrap->Pt_DirectorywrapAsynchro = PtDirectoryWrap;

	return scope.Escape(ObjectSessionWrap);



}
void SessionwrapAsynchro::Init(Local<Object> exports) {

  Isolate* isolate = exports->GetIsolate();
  
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  
  tpl->SetClassName(String::NewFromUtf8(isolate, "SessionwrapAsynchro"));
  
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetUserwrapAsynchro", GetUserwrapAsynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetWASIDAsynchro", GetWASIDAsynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetDirectorywrapAsynchro", GetDirectorywrapAsynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsValidAsynchro", IsValidAsynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "LogOutAsynchro", LogOutAsynchro);

  constructor.Reset(isolate, tpl->GetFunction());
  
  exports->Set(String::NewFromUtf8(isolate, "SessionwrapAsynchro"),
               tpl->GetFunction());
}

void SessionwrapAsynchro::New(const FunctionCallbackInfo<Value>& args) {
  

	Isolate* isolate = args.GetIsolate();

	ControleSession* ControSession = new ControleSession();

	std::string Message;

  if (args.IsConstructCall()) {
	
	  if (ControSession->ControleGetLenght(args, Message, 1)) {


		  SessionwrapAsynchro* PtSessionWrap = new SessionwrapAsynchro();

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
void SessionwrapAsynchro::GetUserwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
	
	
	Isolate* isolate = args.GetIsolate();


	ControleSessionAsynchro* PtControleSessionAsynchro = new ControleSessionAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleSessionAsynchro->ControleGetUserwrapAsynchro(args, controle, Message);

	if (controle == true)
	{

		DataControle Sessiondata = Pt_Vector->at(0);

		Work *work = new Work();

		work->request.data = work;

		SessionwrapAsynchro* PtSessionWrapAsynchro = Sessiondata.Output.PtSessionwrapAsynchro;

		Thread_Data Pt_SessionWrapAsynchro_Intra;

//		ControleSession PtcontroleSession;

		if (PtSessionWrapAsynchro->ptsession->IsValid())
		{
			Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

			work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);

			Local<Function> commeback = Local<Function>::Cast(args[0]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, GetUserwrapAsynchroWork, GetUserwrapAsynchroWorkComplete);

			args.GetReturnValue().Set(Undefined(isolate));
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
void SessionwrapAsynchro::GetUserwrapAsynchroWork(uv_work_t  *request){

	Work *work = (Work*)(request->data);


	Thread_Data Pt_UserWrapAsynchro_Intra;

	Pt_UserWrapAsynchro_Intra.Argument.Ptuser = work->Intra_Data[0].Argument.ptSessionwrapAsynchro->ptsession->GetUser();

	work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);
}
void SessionwrapAsynchro::GetUserwrapAsynchroWorkComplete(uv_work_t  *request, int status){
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	IUser *PtUser = work->Intra_Data[1].Argument.Ptuser;

	Local<Object> ObjectUserwrapAsynchro = UserwrapAsynchro::CreateUserWrapAsynchro(isolate, PtUser, work->Intra_Data[0].Argument.ptSessionwrapAsynchro->Pt_DirectorywrapAsynchro);

	Handle<Value> args[] = { Null(isolate), ObjectUserwrapAsynchro };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}
void SessionwrapAsynchro::GetWASIDAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){


	Isolate* isolate = args.GetIsolate();



	ControleSessionAsynchro* PtControleSessionAsynchro = new ControleSessionAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleSessionAsynchro->ControleGetWASIDAsynchro(args, controle, Message);

	if (controle == true)
	{

		DataControle Sessiondata = Pt_Vector->at(0);

		Work *work = new Work();

		work->request.data = work;

		SessionwrapAsynchro* PtSessionWrapAsynchro = Sessiondata.Output.PtSessionwrapAsynchro;

		Thread_Data Pt_SessionWrapAsynchro_Intra;

		Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

		work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);

		Local<Function> commeback = Local<Function>::Cast(args[0]);

		work->callback.Reset(isolate, commeback);

		uv_queue_work(uv_default_loop(), &work->request, GetWASIDAsynchroWork, GetWASIDAsynchroWorkComplete);

		args.GetReturnValue().Set(Undefined(isolate));

	}

		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetNull();
		}
	


};
void SessionwrapAsynchro::GetWASIDAsynchroWork(uv_work_t  *request){
	Work *work = (Work*)(request->data);

	std::string Resultat = "";
	
	work->Intra_Data[0].Argument.ptSessionwrapAsynchro->ptsession->GetWASID(Resultat);

	Thread_Data Resultat_string;

	Resultat_string.Argument.Resultat_string = new char[Resultat.length() + 1];;

	std::strcpy(Resultat_string.Argument.Resultat_string, Resultat.c_str());

	work->Intra_Data.push_back(Resultat_string);

};
void SessionwrapAsynchro::GetWASIDAsynchroWorkComplete(uv_work_t  *request, int status){
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	char *Resultat_string = work->Intra_Data[1].Argument.Resultat_string;

	Local<String> Resultat_string_v = String::NewFromUtf8(isolate, Resultat_string);

	Handle<Value> args[] = { Null(isolate), Resultat_string_v };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;


};
void SessionwrapAsynchro::GetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){

	Isolate *isolate = Isolate::GetCurrent();

	ControleSessionAsynchro* PtControleSessionAsynchro = new ControleSessionAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleSessionAsynchro->ControleGetDirectorywrapAsynchro(args, controle, Message);

	if (controle == true)
	{

		DataControle Sessiondata = Pt_Vector->at(0);

		Work *work = new Work();

		work->request.data = work;

		SessionwrapAsynchro* PtSessionWrapAsynchro = Sessiondata.Output.PtSessionwrapAsynchro;

		Thread_Data Pt_SessionWrapAsynchro_Intra;

		ControleSession PtcontroleSession;
		if (PtcontroleSession.ControlePtSession(PtSessionWrapAsynchro->ptsession, Message) == true)
		{

			Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

			work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);

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
void SessionwrapAsynchro::GetDirectorywrapAsynchroWork(uv_work_t  *request){
	Work *work = (Work*)(request->data);

	
}
void SessionwrapAsynchro::GetDirectorywrapAsynchroWorkComplete(uv_work_t  *request, int status){

	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	Local<Object> ObjectDirectoryWrap = work->Intra_Data[0].Argument.ptSessionwrapAsynchro->Pt_DirectorywrapAsynchro->handle();

	Handle<Value> args[] = { Null(isolate), ObjectDirectoryWrap };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}
void SessionwrapAsynchro::IsValidAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){

	Isolate* isolate = args.GetIsolate();



	ControleSessionAsynchro* PtControleSessionAsynchro = new ControleSessionAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleSessionAsynchro->ControleIsValidAsynchro(args, controle, Message);

	if (controle == true)
	{

		DataControle Sessiondata = Pt_Vector->at(0);

		Work *work = new Work();

		work->request.data = work;

		SessionwrapAsynchro* PtSessionWrapAsynchro = Sessiondata.Output.PtSessionwrapAsynchro;

		Thread_Data Pt_SessionWrapAsynchro_Intra;

		ControleSession PtcontroleSession;
		if (PtcontroleSession.ControlePtSession(PtSessionWrapAsynchro->ptsession, Message) == true)
		{

			Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

			work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);

			Local<Function> commeback = Local<Function>::Cast(args[0]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, IsValidAsynchroWork, IsValidAsynchroWorkComplete);

			args.GetReturnValue().Set(Undefined(isolate));
		}
	}

	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

		args.GetReturnValue().SetNull();
	}


}
void SessionwrapAsynchro::IsValidAsynchroWork(uv_work_t  *request){
	Work *work = (Work*)(request->data);

	bool Resultat = false;

	Resultat=work->Intra_Data[0].Argument.ptSessionwrapAsynchro->ptsession->IsValid();

	Thread_Data Resultat_data;

	Resultat_data.Argument.Resultat = Resultat;

	work->Intra_Data.push_back(Resultat_data);
};
void SessionwrapAsynchro::IsValidAsynchroWorkComplete(uv_work_t  *request, int status){
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	bool Resultat = work->Intra_Data[1].Argument.Resultat;

	Local<Boolean> Resultat_v8= Boolean::New(isolate, Resultat);

	Handle<Value> args[] = { Null(isolate), Resultat_v8 };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

};
void SessionwrapAsynchro::LogOutAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
	Isolate* isolate = args.GetIsolate();



	ControleSessionAsynchro* PtControleSessionAsynchro = new ControleSessionAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleSessionAsynchro->ControleLogOutAsynchro(args, controle, Message);

	if (controle == true)
	{

		DataControle Sessiondata = Pt_Vector->at(0);

		Work *work = new Work();

		work->request.data = work;

		SessionwrapAsynchro* PtSessionWrapAsynchro = Sessiondata.Output.PtSessionwrapAsynchro;

		Thread_Data Pt_SessionWrapAsynchro_Intra;

		ControleSession PtcontroleSession;
		if (PtcontroleSession.ControlePtSession(PtSessionWrapAsynchro->ptsession, Message) == true)
		{

			Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

			work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);

			Local<Function> commeback = Local<Function>::Cast(args[0]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, LogOutAsynchroWork, LogOutAsynchroWorkComplete);

			args.GetReturnValue().Set(Undefined(isolate));
		}
	}

	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

		args.GetReturnValue().SetNull();
	}

	

};
void SessionwrapAsynchro::LogOutAsynchroWork(uv_work_t  *request){
	
	Work *work = (Work*)(request->data);

	work->Intra_Data[0].Argument.ptSessionwrapAsynchro->ptsession->LogOut();

	

};
void SessionwrapAsynchro::LogOutAsynchroWorkComplete(uv_work_t  *request, int status){

	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	work->Intra_Data[0].Argument.ptSessionwrapAsynchro->ptsession->cookies = "";

	//work->Intra_Data[0].Argument.ptSessionwrapAsynchro->ptsession->cookies = "";

	Handle<Value> args[] = { Null(isolate)};

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 1, args);

	work->callback.Reset();

	delete work;


}

}

