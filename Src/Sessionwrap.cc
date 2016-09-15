#include "Sessionwrap.h"
#include"ControleSessionsynchro.h"
#include"DataControlesyn.h"
#include "Userwrap.h"
#include"Work.h"
#include"Thread_Data.h"
#include"Utility.h"
#include"ControleUsersynchro.h"
#include"DataControlesyn.h"
#include<string>
#include<iostream>
#include"Session.h"
#include"DirectoryWrap.h"
#include"v8.h"
using namespace v8;
using namespace std;
using namespace WaDirectory_Controle;
using namespace WaDirectory_Data;
namespace WaDirectory_View {

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
			
			Tools::Utility util;

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

		Local<v8::Object> ObjectInvoke = Object::New(isolate);

		Local<Boolean> Invoke = Boolean::New(isolate, true);

		ObjectInvoke->Set(String::NewFromUtf8(isolate, "Invoke"), Invoke);

		Local<Value> argv[] = { Boolean::New(isolate, true), ObjectInvoke };

		Local<Context> context = isolate->GetCurrentContext();

		Local<Function> LocalFunct = Local<Function>::New (isolate, Sessionwrap::constructor);

		Local<Object> ObjectSessionWrap = LocalFunct->NewInstance(context, 2, argv).ToLocalChecked();

		Local<Object> obj = Object::New(isolate);

		Sessionwrap* PtSessionWrap = Sessionwrap::Unwrap<Sessionwrap>(ObjectSessionWrap);
		
		PtSessionWrap->ptsession = PtSession;

		PtSessionWrap->ptsession->Pt_Directory=PtDirectoryWrap->ptdirectory;

		PtSessionWrap->Pt_DirectoryWrap = PtDirectoryWrap;

		return scope.Escape(ObjectSessionWrap);



	}
	ISession* Sessionwrap::GetSessionData()
	{
		return this->ptsession;
	}
	void Sessionwrap::Init(Local<Object> exports) {

		Isolate* isolate = exports->GetIsolate();

		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, NewSession);

		tpl->SetClassName(String::NewFromUtf8(isolate, "Session"));

		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		NODE_SET_PROTOTYPE_METHOD(tpl, "GetUser", GetUserwrap);

		NODE_SET_PROTOTYPE_METHOD(tpl, "GetWASID", GetWASID);

		NODE_SET_PROTOTYPE_METHOD(tpl, "GetDirectory", GetDirectorywrap);

		NODE_SET_PROTOTYPE_METHOD(tpl, "IsValid", IsValid);

		NODE_SET_PROTOTYPE_METHOD(tpl, "LogOut", LogOut);

		constructor.Reset(isolate, tpl->GetFunction());

		exports->Set(String::NewFromUtf8(isolate, "Session"),
			tpl->GetFunction());
	}



	void Sessionwrap::NewSession(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		ControleSessionsynchro *PtControleSessionsynchro = new ControleSessionsynchro();

		if (PtControleSessionsynchro->ControleNew(args)) {

			Sessionwrap* PtSessionWrap = new Sessionwrap();

			PtSessionWrap->Wrap(args.This());

			prototype_Session_Synchrone.Reset(isolate, args.This()->GetPrototype());

			args.GetReturnValue().Set(args.Holder());

			
			
		}
		else
		{

			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "To create a object of Session  you need to pass from Directory object ")));

			args.GetReturnValue().SetUndefined();

		}
		delete PtControleSessionsynchro;

	}

	void Sessionwrap::GetUserwrap(const FunctionCallbackInfo<Value>& args) {

		Isolate* isolate = args.GetIsolate();

		ControleSessionsynchro *PtControleSessionsynchro = new ControleSessionsynchro();

		Local<Context> contexttest = isolate->GetCurrentContext();

		bool Controle = false;

		string Message;

		vector<DataControlesyn>* Pt_Vector = PtControleSessionsynchro->ControleGetUserwrapsynchro(args, Controle, Message);

		if (Controle == true)
		{
			DataControlesyn Sessiondata = Pt_Vector->at(0);

			Work *work = new Work();

			work->request.data = work;

			Sessionwrap* PtSessionWrap = Sessiondata.Output.PtSessionwrap;

			Thread_Data Pt_SessionWrap_Intra;


			if (PtSessionWrap->ptsession->IsValid())
			{
				Pt_SessionWrap_Intra.Argument.ptSessionwrap = PtSessionWrap;

				work->Intra_Data.push_back(Pt_SessionWrap_Intra);

				Local<Function> commeback = Local<Function>::Cast(args[0]);

				work->callback.Reset(isolate, commeback);

				uv_queue_work(uv_default_loop(), &work->request, GetUserwrapWork, GetUserwrapWorkComplete);

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

		delete PtControleSessionsynchro;
		
		
	}

	void Sessionwrap::GetUserwrapWork(uv_work_t  *request)
	{
		Work *work = (Work*)(request->data);


		Thread_Data Pt_UserWrap_Intra;

		Pt_UserWrap_Intra.Argument.Ptuser = work->Intra_Data[0].Argument.ptSessionwrap->ptsession->GetUser();

		work->Intra_Data.push_back(Pt_UserWrap_Intra);

	}
	void Sessionwrap::GetUserwrapWorkComplete(uv_work_t  *request, int status)
	{
		Isolate *isolate = Isolate::GetCurrent();

		HandleScope scoop(isolate);

		Work *work = (Work *)(request->data);

		IUser *PtUser = work->Intra_Data[1].Argument.Ptuser;
		Local<Object> ObjectUserwrap;
		if (PtUser!=NULL)
		{ 

		
			ObjectUserwrap = Userwrap::CreateUserWrap(isolate, PtUser, work->Intra_Data[0].Argument.ptSessionwrap->Pt_DirectoryWrap);
		}
		Handle<Value> args[] = { Null(isolate), ObjectUserwrap };

		Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

		work->callback.Reset();

		delete work;

		

	}

	void Sessionwrap::GetWASID(const FunctionCallbackInfo<Value>& args) {

		Isolate* isolate = args.GetIsolate();


		ControleSessionsynchro *PtControleSessionsynchro = new ControleSessionsynchro();

		bool Controle = false;

		string Message;

		vector<DataControlesyn>* Pt_Vector = PtControleSessionsynchro->ControleGetWASIDsynchro(args, Controle, Message);

		if (Controle == true)
		{
			DataControlesyn Sessiondata = Pt_Vector->at(0);

			Sessionwrap* PtSessionWrap = Sessiondata.Output.PtSessionwrap;

			std::string resultat = PtSessionWrap->ptsession->cookies;

			args.GetReturnValue().Set(String::NewFromUtf8(isolate, resultat.c_str()));
			
		
		}
		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetNull();
		}

		delete PtControleSessionsynchro;
	}

	void Sessionwrap::GetDirectorywrap(const FunctionCallbackInfo<Value>& args) {

		Isolate* isolate = args.GetIsolate();

		ControleSessionsynchro *PtControleSessionsynchro = new ControleSessionsynchro();

		bool Controle = false;

		string Message;

		vector<DataControlesyn>* Pt_Vector = PtControleSessionsynchro->ControleGetDirectorywrapsynchro(args, Controle, Message);

		if (Controle == true)
		{
			DataControlesyn Sessiondata = Pt_Vector->at(0);

			Sessionwrap* PtSessionWrap = Sessiondata.Output.PtSessionwrap;

			Local<Object> ObjectDirectoryWrap = PtSessionWrap->Pt_DirectoryWrap->handle();

			args.GetReturnValue().Set(ObjectDirectoryWrap);

		}

		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetNull();
		}
		delete PtControleSessionsynchro;
	
	}

	void Sessionwrap::IsValid(const FunctionCallbackInfo<Value>& args) {

		Isolate* isolate = args.GetIsolate();

		ControleSessionsynchro *PtControleSessionsynchro = new ControleSessionsynchro();

		bool Controle = false;

		string Message;

		vector<DataControlesyn>* Pt_Vector = PtControleSessionsynchro->ControleIsValidsynchro(args, Controle, Message);

		if (Controle == true)
		{
			DataControlesyn Sessiondata = Pt_Vector->at(0);

			Work *work = new Work();

			work->request.data = work;

			Sessionwrap* PtSessionWrap = Sessiondata.Output.PtSessionwrap;

			Thread_Data Pt_SessionWrap_Intra;

			Pt_SessionWrap_Intra.Argument.ptSessionwrap = PtSessionWrap;

			work->Intra_Data.push_back(Pt_SessionWrap_Intra);

			Local<Function> commeback = Local<Function>::Cast(args[0]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, IsValidWork, IsValidWorkComplete);

			args.GetReturnValue().Set(Undefined(isolate));
			
			
		}

		else
			{
				isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

				args.GetReturnValue().SetNull();
			}

		delete PtControleSessionsynchro;
	}
	void Sessionwrap::IsValidWork(uv_work_t  *request)
	{
		Work *work = (Work*)(request->data);

		bool Resultat = false;

		Resultat = work->Intra_Data[0].Argument.ptSessionwrap->ptsession->IsValid();

		Thread_Data Resultat_data;

		Resultat_data.Argument.Resultat = Resultat;

		work->Intra_Data.push_back(Resultat_data);
	}
	void Sessionwrap::IsValidWorkComplete(uv_work_t  *request, int status)
	{
		Isolate *isolate = Isolate::GetCurrent();

		HandleScope scoop(isolate);

		Work *work = (Work *)(request->data);

		bool Resultat = work->Intra_Data[1].Argument.Resultat;

		Local<Boolean> Resultat_v8 = Boolean::New(isolate, Resultat);

		Handle<Value> args[] = { Null(isolate), Resultat_v8 };

		Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

		work->callback.Reset();

		delete work;
	}
	void Sessionwrap::LogOut(const FunctionCallbackInfo<Value>& args) {

		Isolate* isolate = args.GetIsolate();

		ControleSessionsynchro *PtControleSessionsynchro = new ControleSessionsynchro();

		bool Controle = false;

		string Message;

		vector<DataControlesyn>* Pt_Vector = PtControleSessionsynchro->ControleLogOutsynchro(args, Controle, Message);

		if (Controle == true)
		{
			DataControlesyn Sessiondata = Pt_Vector->at(0);

			Sessionwrap* PtSessionWrap = Sessiondata.Output.PtSessionwrap;

			PtSessionWrap->ptsession->LogOut();
			
			PtSessionWrap->ptsession->cookies = "";

			args.GetReturnValue().SetUndefined();
			
		}
		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetNull();
		}
		delete PtControleSessionsynchro;

	}



}
