#include "Directorywrap.h"
#include"Utility.h"
#include"ControleDirectorysynchro.h"
#include<vector>
#include<string>
#include<iostream>
#include"v8.h"
#include"Work.h"
#include"Thread_Data.h"
using namespace v8;
using namespace WaDirectory_Data;
using namespace std;
using namespace WaDirectory_Controle;
using namespace Tools;
namespace WaDirectory_View {
Persistent<Function> Directorywrap::constructor;

Persistent<Value> Directorywrap::prototype_Directory_Synchrone;


Local<Boolean> Directorywrap::ControleDirectoryUnwrap(Local<Object> handle, Isolate* isolate)
{
	EscapableHandleScope scope(isolate);

	if (!handle.IsEmpty() && handle->InternalFieldCount() == 1) {

		Local<Value> Pt_Prototype = handle->GetPrototype();
		
		Tools::Utility util;

		if (Pt_Prototype == prototype_Directory_Synchrone) {
			Local<Boolean> Resultat = Boolean::New(isolate, true);
			return scope.Escape(Resultat);

		}


	}
	Local<Boolean> Resultat = Boolean::New(isolate, false);
	return scope.Escape(Resultat);
}
Directorywrap::Directorywrap() :ptdirectory() {
	
}

Directorywrap::~Directorywrap() {
}
IDirectory* Directorywrap::GetDirectory()
{
	return this->ptdirectory;
}

void Directorywrap::Init(Local<Object> exports) {

	Isolate* isolate = exports->GetIsolate();


	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);

	tpl->SetClassName(String::NewFromUtf8(isolate, "Directorywrap"));
  
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	NODE_SET_PROTOTYPE_METHOD(tpl, "LogIn", LogIn);

	NODE_SET_PROTOTYPE_METHOD(tpl, "GetGroupwrapNames", GetGroupwrapNames);
  
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetGroupwrap", GetGroupwrap);
  
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetUserwrap", GetUserwrap);
  
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetSessionwrap", GetSessionwrap);
  
	NODE_SET_PROTOTYPE_METHOD(tpl, "UserwrapBelongTo", UserwrapBelongTo);
 
	NODE_SET_PROTOTYPE_METHOD(tpl, "LogOut", LogOut);
	
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetGroupwrapID", GetGroupwrapID);

    constructor.Reset(isolate, tpl->GetFunction());
  
	exports->Set(String::NewFromUtf8(isolate, "Directorywrap"),
               tpl->GetFunction());
}

void Directorywrap::New(const FunctionCallbackInfo<Value>& args) {
  
  Isolate* isolate = args.GetIsolate();
  
  std::string Message;
  
if (args.Length() == 2) 
  {

	
		  if ((args[0]->IsString())&&(args[1]->IsString()))
		  { 

			 
			      Tools::Utility util;

				  std::string Url_Wakanda = util.V8Utf8ValueToStdString(args[0]);

				  std::string Url_Directory = util.V8Utf8ValueToStdString(args[1]);

				  Directorywrap* Obj_Directory_Wrap = new Directorywrap();

				  IDirectory *Pt_Directory = new Directory(Url_Wakanda, Url_Directory);

				  Obj_Directory_Wrap->ptdirectory = Pt_Directory;

				  Obj_Directory_Wrap->Wrap(args.This());

				  prototype_Directory_Synchrone.Reset(isolate, args.This()->GetPrototype());

				  args.GetReturnValue().Set(args.This());
			  
		  }
		  else
		  {
			  isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "the arguments need to be string value")));
			  
	
			  
		  }
	}

    else {

	         isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
	         
		
			
  }
}

void Directorywrap::LogIn(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	ControleDirectorysynchro *PtControleDirectorysynchro = new ControleDirectorysynchro();
	
	Local<Context> contexttest = isolate->GetCurrentContext();
	
	bool controle = false;

	std::string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleDirectorysynchro->ControleLogInsynchro(args, controle, Message);

	if (controle == true)
	{
		Work *work = new Work();

		work->request.data = work;

		DataControlesyn Directorydata = Pt_Vector->at(0);

		Directorywrap* PtDirectorywrap = Directorydata.Output.PtDirectorywrap;

		Thread_Data Pt_DirectoryWrap_Intra;

		Pt_DirectoryWrap_Intra.Argument.PtDirectorywrap = PtDirectorywrap;

		work->Intra_Data.push_back(Pt_DirectoryWrap_Intra);

		DataControlesyn Userdata = Pt_Vector->at(1);

		Userwrap* PtUserWrap = Userdata.Output.PtUserwrap;

		string user = PtUserWrap->ptuser->Username;

		string password = PtUserWrap->ptuser->Password;

		Thread_Data Pt_User;

		Pt_User.Argument.user = new char[user.length() + 1];;

		std::strcpy(Pt_User.Argument.user, user.c_str());

		work->Input_Data.push_back(Pt_User);

		Thread_Data Pt_Password;

		Pt_Password.Argument.password = new char[password.length() + 1];

		std::strcpy(Pt_Password.Argument.password, password.c_str());

		work->Input_Data.push_back(Pt_Password);

		Local<Function> commeback = Local<Function>::Cast(args[1]);

		work->callback.Reset(isolate, commeback);

		uv_queue_work(uv_default_loop(), &work->request, LogInWork, LogInWorkComplete);

		args.GetReturnValue().Set(Undefined(isolate));

	}
	

	else
	{

		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
		args.GetReturnValue().SetNull();

	}
	
	delete PtControleDirectorysynchro;

}

void Directorywrap::LogInWork(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);

	string user = work->Input_Data[0].Argument.user;

	string password = work->Input_Data[1].Argument.password;

	Thread_Data Pt_SessionWrap_Intra;

	Pt_SessionWrap_Intra.Argument.PtSession = work->Intra_Data[0].Argument.PtDirectorywrap->ptdirectory->LogIn(user, password);

	work->Intra_Data.push_back(Pt_SessionWrap_Intra);

}
void Directorywrap::LogInWorkComplete(uv_work_t  *request, int status)
{
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	ISession *PtSession = work->Intra_Data[1].Argument.PtSession;

	Local<Object> ObjectSessionwrap = Sessionwrap::CreateSessionWrap(isolate, PtSession, work->Intra_Data[0].Argument.PtDirectorywrap);

	Handle<Value> args[] = { Null(isolate), ObjectSessionwrap };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}
void Directorywrap::GetGroupwrapID(const v8::FunctionCallbackInfo<v8::Value>& args)
{

	Isolate* isolate = args.GetIsolate();

	ControleDirectorysynchro *PtControleDirectorysynchro = new ControleDirectorysynchro();

	bool controle = false;

	std::string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleDirectorysynchro->ControleGetGroupwrapIDsynchro(args, controle, Message);
	if (controle == true)
	{
		DataControlesyn Directorydata = Pt_Vector->at(0);

		Directorywrap* PtDirectoryWrap = Directorydata.Output.PtDirectorywrap;

		std::vector<std::string> Vector;

		PtDirectoryWrap->ptdirectory->GetGroupId(Vector);

		Tools::Utility util;

		Local<Array> Resulat = util.StdVectorToV8Array(isolate, Vector);

		args.GetReturnValue().Set(Resulat);
	}

	else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetNull();

		}

	delete PtControleDirectorysynchro;
	
}
void Directorywrap::GetGroupwrapNames(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	ControleDirectorysynchro *PtControleDirectorysynchro = new ControleDirectorysynchro();

	bool controle = false;

	std::string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleDirectorysynchro->ControleGetGroupwrapNamessynchro(args, controle, Message);
	if (controle == true)
	{
		DataControlesyn Directorydata = Pt_Vector->at(0);

		Directorywrap* PtDirectoryWrap = Directorydata.Output.PtDirectorywrap;

		std::vector<std::string> Vector;

		PtDirectoryWrap->ptdirectory->GetGroupNames(Vector);

		Tools::Utility util;

		Local<Array> Resulat = util.StdVectorToV8Array(isolate, Vector);

		args.GetReturnValue().Set(Resulat);
	}

	else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetNull();

		}

	delete PtControleDirectorysynchro;
	
}
void Directorywrap::GetGroupwrap(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();

	ControleDirectorysynchro *PtControleDirectorysynchro = new ControleDirectorysynchro();

	bool controle = false;

	std::string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleDirectorysynchro->ControleGetGroupwrapsynchro(args, controle, Message);
	if (controle == true)
	{
		DataControlesyn Directorydata = Pt_Vector->at(0);

		Directorywrap* PtDirectoryWrap = Directorydata.Output.PtDirectorywrap;

		DataControlesyn GroupIddata = Pt_Vector->at(1);

		string GroupId = GroupIddata.Output.GroupId;

		IGroup* PtGroup = PtDirectoryWrap->ptdirectory->GetGroup(GroupId);

		if (PtGroup != NULL)
		{

			Local<Object> ObjectGroupWrap = Groupwrap::CreateGroupWrap(isolate, PtGroup, PtDirectoryWrap);

			args.GetReturnValue().Set(ObjectGroupWrap);
		}
		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a GroupId")));
			args.GetReturnValue().SetNull();
		}
	}

	else{

			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetUndefined();
		}
	
	delete PtControleDirectorysynchro;
}
void Directorywrap::GetUserwrap(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	ControleDirectorysynchro *PtControleDirectorysynchro = new ControleDirectorysynchro();

	bool controle = false;

	std::string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleDirectorysynchro->ControleGetUserwrapsynchro(args, controle, Message);
	if (controle == true)
	{
		DataControlesyn Directorydata = Pt_Vector->at(0);

		Directorywrap* PtDirectoryWrap = Directorydata.Output.PtDirectorywrap;

		DataControlesyn UserIddata = Pt_Vector->at(1);

		string UserId = UserIddata.Output.UserId;

		DataControlesyn Passworddata = Pt_Vector->at(2);

		string Password = Passworddata.Output.Password;

		bool resultat = false;

		resultat = PtDirectoryWrap->ptdirectory->Existbyname(UserId);

		resultat = PtDirectoryWrap->ptdirectory->Isvalid(UserId, Password);


		IUser* PtUser = NULL;
		if (resultat)
		{
			PtUser = PtDirectoryWrap->ptdirectory->GetUser(UserId, Password);


		}
		if (PtUser)
		{

			Local<Object> ObjectUserWrap = Userwrap::CreateUserWrap(isolate, PtUser, PtDirectoryWrap);


			args.GetReturnValue().Set(ObjectUserWrap);
		}
		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a UserId")));
			args.GetReturnValue().SetNull();
		}
	}

	else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetUndefined();
		}
	
	delete PtControleDirectorysynchro;
}
void Directorywrap::GetSessionwrap(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	ControleDirectorysynchro *PtControleDirectorysynchro = new ControleDirectorysynchro();

	bool controle = false;

	std::string Message;
	
	int Methode = 0;

	vector<DataControlesyn>* Pt_Vector = PtControleDirectorysynchro->ControleGetSessionwrapsynchro(args, controle, Message,Methode);
	if (controle == true)
	{
		if (Methode==1)
		{ 
		Work *work = new Work();

		work->request.data = work;

		DataControlesyn Directorydata = Pt_Vector->at(0);

		Directorywrap* PtDirectorywrap = Directorydata.Output.PtDirectorywrap;

		Thread_Data Pt_DirectoryWrap_Intra;

		Pt_DirectoryWrap_Intra.Argument.PtDirectorywrap = PtDirectorywrap;

		work->Intra_Data.push_back(Pt_DirectoryWrap_Intra);

		DataControlesyn IdSessiondata = Pt_Vector->at(1);

		Thread_Data Pt_SessionId;

		Pt_SessionId.Argument.SessionId = IdSessiondata.Output.SessionId;

		work->Input_Data.push_back(Pt_SessionId);

		Local<Function> commeback = Local<Function>::Cast(args[1]);

		work->callback.Reset(isolate, commeback);

		uv_queue_work(uv_default_loop(), &work->request, GetSessionwrapWork1, GetSessionwrapWorkComplete1);

		args.GetReturnValue().Set(Undefined(isolate));

		}
	}
else{

			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetNull();

		}

delete PtControleDirectorysynchro;
	
	
}

void Directorywrap::GetSessionwrapWork1(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);

	string SessionId = work->Input_Data[0].Argument.SessionId;

	Thread_Data Pt_SessionWrap_Intra;

	Pt_SessionWrap_Intra.Argument.PtSession = work->Intra_Data[0].Argument.PtDirectorywrap->ptdirectory->GetSession(SessionId);

	work->Intra_Data.push_back(Pt_SessionWrap_Intra);
}
void Directorywrap::GetSessionwrapWorkComplete1(uv_work_t  *request, int status)
{
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	ISession *PtSession = work->Intra_Data[1].Argument.PtSession;

	Local<Object> ObjectSessionwrap = Sessionwrap::CreateSessionWrap(isolate, PtSession, work->Intra_Data[0].Argument.PtDirectorywrap);

	Handle<Value> args[] = { Null(isolate), ObjectSessionwrap };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;
}
void Directorywrap::GetSessionwrapWok2(uv_work_t  *request)
{

}
void Directorywrap::GetSessionwrapWorkComplete2(uv_work_t  *request, int status)
{

}
void Directorywrap::UserwrapBelongTo(const FunctionCallbackInfo<Value>& args) {


	Isolate* isolate = args.GetIsolate();

	ControleDirectorysynchro *PtControleDirectorysynchro = new ControleDirectorysynchro();

	bool controle = false;

	std::string Message;

	int Methode = 0;

	vector<DataControlesyn>* Pt_Vector = PtControleDirectorysynchro->ControleUserwrapBelongTosynchro(args, controle, Message,Methode);
	
	if (controle == true)
	{
		Work *work = new Work();

		work->request.data = work;

		DataControlesyn Directorydata = Pt_Vector->at(0);

		Directorywrap* PtDirectorywrap = Directorydata.Output.PtDirectorywrap;

		Thread_Data Pt_DirectoryWrap_Intra;

		Pt_DirectoryWrap_Intra.Argument.PtDirectorywrap = PtDirectorywrap;

		work->Intra_Data.push_back(Pt_DirectoryWrap_Intra);
		if (Methode == 1)
		{
			DataControlesyn Userdata = Pt_Vector->at(1);

			Userwrap* PtUserWrap = Userdata.Output.PtUserwrap;

			Thread_Data Pt_UserWrap_Intra;

			Pt_UserWrap_Intra.Argument.PtUserwrap = PtUserWrap;

			work->Intra_Data.push_back(Pt_UserWrap_Intra);

			DataControlesyn GroupIddata = Pt_Vector->at(2);

			Thread_Data Pt_inGroupID;

			Pt_inGroupID.Argument.GroupId = GroupIddata.Output.GroupId;

			work->Input_Data.push_back(Pt_inGroupID);

			Local<Function> commeback = Local<Function>::Cast(args[2]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, UserwrapBelongToWork2, UserwrapBelongToWorkComplete2);

			args.GetReturnValue().Set(Undefined(isolate));

		}
		if (Methode == 2)
		{
			DataControlesyn Userdata = Pt_Vector->at(1);

			Userwrap* PtUserWrap = Userdata.Output.PtUserwrap;

			Thread_Data Pt_UserWrap_Intra;

			Pt_UserWrap_Intra.Argument.PtUserwrap = PtUserWrap;

			work->Intra_Data.push_back(Pt_UserWrap_Intra);

			DataControlesyn Groupdata = Pt_Vector->at(2);

			Groupwrap* PtGroupWrap = Groupdata.Output.PtGroupwrap;

			Thread_Data Pt_GroupWrap_Intra;

			Pt_GroupWrap_Intra.Argument.PtGroupWrap = PtGroupWrap;

			work->Intra_Data.push_back(Pt_GroupWrap_Intra);


			Local<Function> commeback = Local<Function>::Cast(args[2]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, UserwrapBelongToWork3, UserwrapBelongToWorkComplete3);

			args.GetReturnValue().Set(Undefined(isolate));
		}
		if (Methode == 3)
		{
			DataControlesyn Sessiondata = Pt_Vector->at(1);

			Sessionwrap* PtSessionWrap = Sessiondata.Output.PtSessionwrap;

			Thread_Data Pt_SessionWrap_Intra;

			Pt_SessionWrap_Intra.Argument.ptSessionwrap = PtSessionWrap;

			work->Intra_Data.push_back(Pt_SessionWrap_Intra);

			DataControlesyn GroupIddata = Pt_Vector->at(2);

			Thread_Data Pt_inGroupID;

			Pt_inGroupID.Argument.GroupId = GroupIddata.Output.GroupId;

			work->Input_Data.push_back(Pt_inGroupID);

			Local<Function> commeback = Local<Function>::Cast(args[2]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, UserwrapBelongToWork1, UserwrapBelongToWorkComplete1);

			args.GetReturnValue().Set(Undefined(isolate));
		}
	}

	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

		args.GetReturnValue().SetUndefined();
	}

	delete PtControleDirectorysynchro;
}

void Directorywrap::UserwrapBelongToWork1(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);

	string GroupId = work->Input_Data[0].Argument.GroupId;

	Sessionwrap* PtSessionWrap = work->Intra_Data[1].Argument.ptSessionwrap;

	Thread_Data Resultat_Intra;

	Resultat_Intra.Argument.Resultat = work->Intra_Data[0].Argument.PtDirectorywrap->ptdirectory->UserBelongTo(PtSessionWrap->ptsession, GroupId);

	work->Intra_Data.push_back(Resultat_Intra);
}
void Directorywrap::UserwrapBelongToWorkComplete1(uv_work_t  *request, int status)
{
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	bool Resultat = work->Intra_Data[2].Argument.Resultat;

	Local<Boolean> Resultat_v8 = Boolean::New(isolate, Resultat);

	Handle<Value> args[] = { Null(isolate), Resultat_v8 };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;
}
void Directorywrap::UserwrapBelongToWork2(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);

	string GroupId = work->Input_Data[0].Argument.GroupId;

	Userwrap* PtUserWrap = work->Intra_Data[1].Argument.PtUserwrap;

	Thread_Data Resultat_Intra;

	Resultat_Intra.Argument.Resultat = work->Intra_Data[0].Argument.PtDirectorywrap->ptdirectory->UserBelongTo(PtUserWrap->ptuser, GroupId);

	work->Intra_Data.push_back(Resultat_Intra);
}
void Directorywrap::UserwrapBelongToWorkComplete2(uv_work_t  *request, int status)
{
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	bool Resultat = work->Intra_Data[2].Argument.Resultat;

	Local<Boolean> Resultat_v8 = Boolean::New(isolate, Resultat);

	Handle<Value> args[] = { Null(isolate), Resultat_v8 };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;
}
void Directorywrap::UserwrapBelongToWork3(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);

	Groupwrap* PtGroupWrap = work->Intra_Data[2].Argument.PtGroupWrap;

	Userwrap* PtUserWrap = work->Intra_Data[1].Argument.PtUserwrap;

	Thread_Data Resultat_Intra;

	Resultat_Intra.Argument.Resultat = work->Intra_Data[0].Argument.PtDirectorywrap->ptdirectory->UserBelongTo(PtUserWrap->ptuser, PtGroupWrap->ptgroup);

	work->Intra_Data.push_back(Resultat_Intra);
}
void Directorywrap::UserwrapBelongToWorkComplete3(uv_work_t  *request, int status)
{
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	bool Resultat = work->Intra_Data[3].Argument.Resultat;

	Local<Boolean> Resultat_v8 = Boolean::New(isolate, Resultat);

	Handle<Value> args[] = { Null(isolate), Resultat_v8 };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}
void Directorywrap::LogOut(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	ControleDirectorysynchro *PtControleDirectorysynchro = new ControleDirectorysynchro();

	bool controle = false;

	std::string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleDirectorysynchro->ControleLogOutsynchro1(args, controle, Message);
	if (controle == true)
	{
		DataControlesyn Directorydata = Pt_Vector->at(0);

		Directorywrap* PtDirectoryWrap = Directorydata.Output.PtDirectorywrap;

		DataControlesyn Sessiondata = Pt_Vector->at(1);

		Sessionwrap* PtSessionWrap = Sessiondata.Output.PtSessionwrap;

		bool resultat = PtDirectoryWrap->ptdirectory->LogOut(PtSessionWrap->ptsession);

		args.GetReturnValue().Set(Boolean::New(isolate, resultat));

	}
else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetUndefined();
		}

	delete PtControleDirectorysynchro;
}


} 