#include "Directorywrap.h"
#define _HAS_EXCEPTIONS 0
#include"Utility.h"
#include"ControleDirectorysynchro.h"
#include<vector>
#include<string>
#include<iostream>
#include"SessionLog.h"
#include"v8.h"
#include"Work.h"
#include<thread>
#include <chrono>
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

	tpl->SetClassName(String::NewFromUtf8(isolate, "Directory"));
  
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	NODE_SET_PROTOTYPE_METHOD(tpl, "LogIn", LogIn);

	NODE_SET_PROTOTYPE_METHOD(tpl, "GetGroupsNames", GetGroupwrapNames);
  
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetGroup", GetGroupwrap);
  
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetUser", GetUserwrap);
  
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetSession", GetSessionwrap);
  
	NODE_SET_PROTOTYPE_METHOD(tpl, "UserBelongTo", UserwrapBelongTo);
 
	NODE_SET_PROTOTYPE_METHOD(tpl, "LogOut", LogOut);
	
	NODE_SET_PROTOTYPE_METHOD(tpl, "GetGroupsID", GetGroupwrapID);

	NODE_SET_PROTOTYPE_METHOD(tpl, "Getcookies", Getcookies);

	NODE_SET_PROTOTYPE_METHOD(tpl, "getlistmanager", getlistmanager);

	NODE_SET_PROTOTYPE_METHOD(tpl, "getusersid", GetUserswrapID);
	
	NODE_SET_PROTOTYPE_METHOD(tpl, "getusers", GetUsers);

	NODE_SET_PROTOTYPE_METHOD(tpl, "getsessionlog", getsessionlog);

    constructor.Reset(isolate, tpl->GetFunction());
  
	exports->Set(String::NewFromUtf8(isolate, "Directory"),
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

				  
				 std::thread threadSession(&ManageSession::Task, &Pt_Directory->List, 30000, Pt_Directory,std::ref(Pt_Directory->List.list));

				  

				 if (threadSession.joinable())
				  {
					  threadSession.detach();
				  }
				  
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


		Thread_Data Pt_User1;
		
		Pt_User1.Argument.PtUserwrap = PtUserWrap;

		work->Input_Data.push_back(Pt_User1);

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
	
	Local<Object> ObjectSessionwrap;

	if (PtSession!=NULL)
	{ 

	ObjectSessionwrap = Sessionwrap::CreateSessionWrap(isolate, PtSession, work->Intra_Data[0].Argument.PtDirectorywrap);

	Sessionwrap *_Pt_Session = Unwrap<Sessionwrap>(ObjectSessionwrap);

	Local<Context> CurrentContext = isolate->GetCurrentContext();

	CurrentContext->SetEmbedderData(0, ObjectSessionwrap);

	Directorywrap* _PtDirectory = work->Intra_Data[0].Argument.PtDirectorywrap;

	Userwrap* _PtUserwrap = work->Input_Data[2].Argument.PtUserwrap;
	
	Handle<Value> args[] = { Null(isolate), ObjectSessionwrap };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	}
	else
	{
		Handle<Value> args[] = { Null(isolate)};
		Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 1, args);

	}

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
void Directorywrap::GetUserswrapID(const v8::FunctionCallbackInfo<v8::Value>& args)
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

		PtDirectoryWrap->ptdirectory->GetUsersId(Vector);

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

void Directorywrap::GetUsers(const v8::FunctionCallbackInfo<v8::Value>& args)
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

		PtDirectoryWrap->ptdirectory->GetUsersId(Vector);

		Tools::Utility util;

		Local<Array> Resultat = Array::New(isolate);
		int i = 0;
		for (auto const& Iterator : Vector) {

			IUser *PtUser = PtDirectoryWrap->ptdirectory->GetUserById(Iterator);

			Local<Object> ObjectUserWrap = Userwrap::CreateUserWrap(isolate, PtUser, PtDirectoryWrap);

			Resultat->Set(i, ObjectUserWrap);
			i++;
		}

		

		args.GetReturnValue().Set(Resultat);
	}

	else
	{
		//isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
		args.GetReturnValue().SetNull();

	}

	delete PtControleDirectorysynchro;

}

void Directorywrap::getsessionlog(const v8::FunctionCallbackInfo<v8::Value>& args)
{
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

		Local<Array> Tab = Array::New(isolate);

		vector<SessionLog> Resultat=PtDirectoryWrap->ptdirectory->loadfile();
		
		int Index = 0;
		for (auto Iterator : Resultat){

			Local<Object> object1 = Object::New(isolate);

			object1->Set(String::NewFromUtf8(isolate, "OperationTime"), String::NewFromUtf8(isolate, Iterator.OperationTime.c_str()));
			object1->Set(String::NewFromUtf8(isolate, "TypeOperation"), String::NewFromUtf8(isolate, Iterator.TypeOperation.c_str()));
			object1->Set(String::NewFromUtf8(isolate, "wsid"), String::NewFromUtf8(isolate, Iterator.wsid.c_str()));
			object1->Set(String::NewFromUtf8(isolate, "IdUser"), String::NewFromUtf8(isolate, Iterator.IdUser.c_str()));
			object1->Set(String::NewFromUtf8(isolate, "NameUser"), String::NewFromUtf8(isolate, Iterator.NameUser.c_str()));
			Tab->Set(Index, object1);
			Index++;
		}

		args.GetReturnValue().Set(Tab);
	}

	else
	{
		//isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
		args.GetReturnValue().SetNull();

	}

	delete PtControleDirectorysynchro;

}


void Directorywrap::getlistmanager(const v8::FunctionCallbackInfo<v8::Value>& args)
{
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

		Local<Array> Tab = Array::New(isolate);

		PtDirectoryWrap->ptdirectory->List;

		int Index = 0;

		for (auto Iterator : PtDirectoryWrap->ptdirectory->List.list){

			Local<Object> object1 = Object::New(isolate);

			object1->Set(String::NewFromUtf8(isolate, "IdUser"), String::NewFromUtf8(isolate, Iterator.IdUser.c_str()));
			object1->Set(String::NewFromUtf8(isolate, "Username"), String::NewFromUtf8(isolate, Iterator.Username.c_str()));
			object1->Set(String::NewFromUtf8(isolate, "WSID"), String::NewFromUtf8(isolate, Iterator.getWASID().c_str()));
			object1->Set(String::NewFromUtf8(isolate, "TTL"), Number::New(isolate, Iterator.MaxAgeTtl));
			Tab->Set(Index, object1);
			Index++;

		}
		
		args.GetReturnValue().Set(Tab);
	}

	else
	{
		//isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
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

void Directorywrap::Getcookies(const FunctionCallbackInfo<Value>& args)
{
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

		string cookiesid = GroupIddata.Output.GroupId;
		
		bool etat =PtDirectoryWrap->ptdirectory->List.findcookiesbywsid(cookiesid);

		if (etat==true)
		{

			args.GetReturnValue().Set(String::NewFromUtf8(isolate,cookiesid.c_str()));
		}
		else
		{
			//isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a GroupId")));
			args.GetReturnValue().SetNull();
		}
	}

	else{

		//isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

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

			Local<Object> ObjectGroupWrap = Groupwrap::CreateGroupWrap(isolate, PtGroup, PtDirectoryWrap, PtDirectoryWrap->ptdirectory);

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
			//isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a UserId")));
			args.GetReturnValue().SetNull();
		}
	}

	else
		{
			//isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetNull();
		}
	
	delete PtControleDirectorysynchro;
}
void Directorywrap::validate(const v8::FunctionCallbackInfo<v8::Value>& args)
{

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
		if (Methode == 1)
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
		if (Methode == 2)
		{
			Work *work = new Work();

			work->request.data = work;

			DataControlesyn Directorydata = Pt_Vector->at(0);

			Directorywrap* PtDirectorywrap = Directorydata.Output.PtDirectorywrap;

			Thread_Data Pt_DirectoryWrap_Intra;

			Pt_DirectoryWrap_Intra.Argument.PtDirectorywrap = PtDirectorywrap;

			work->Intra_Data.push_back(Pt_DirectoryWrap_Intra);

			DataControlesyn IdSessiondata = Pt_Vector->at(1);

			Thread_Data Pt_Session;

			Pt_Session.Argument.ptSessionwrap = IdSessiondata.Output.PtSessionwrap;

			work->Input_Data.push_back(Pt_Session);

			Local<Function> commeback = Local<Function>::Cast(args[0]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, GetSessionwrapWok2, GetSessionwrapWorkComplete2);

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

	Local<Object> ObjectSessionwrap;
	if (PtSession!=NULL)
	{ 
	
		ObjectSessionwrap = Sessionwrap::CreateSessionWrap(isolate, PtSession, work->Intra_Data[0].Argument.PtDirectorywrap);
	
		Local<Context> CurrentContext = isolate->GetCurrentContext();

		CurrentContext->SetEmbedderData(0, ObjectSessionwrap);
	
	}
	Handle<Value> args[] = { Null(isolate), ObjectSessionwrap };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;
}
void Directorywrap::GetSessionwrapWok2(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);

	Sessionwrap* PtSession = work->Input_Data[0].Argument.ptSessionwrap;

	Thread_Data Pt_SessionWrap_Intra;

	Pt_SessionWrap_Intra.Argument.ptSessionwrap = PtSession;

	work->Intra_Data.push_back(Pt_SessionWrap_Intra);

}
void Directorywrap::GetSessionwrapWorkComplete2(uv_work_t  *request, int status)
{
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	Sessionwrap *PtSessionwrap = work->Intra_Data[1].Argument.ptSessionwrap;

	Local<Object> ObjectSessionwrap;
	if (PtSessionwrap != NULL)
	{

		ObjectSessionwrap = PtSessionwrap->handle();
	}
	Handle<Value> args[] = { Null(isolate), ObjectSessionwrap };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;
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
		if ((Methode == 4) || (Methode == 3))
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
			
			Local<Function> commeback;
			
			if (Methode == 3)
			{ 
				commeback = Local<Function>::Cast(args[2]);
			}
			if(Methode == 4)
			{ 
				commeback = Local<Function>::Cast(args[1]);
			}
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

		PtDirectoryWrap->ptdirectory->List.RemoveBycookies(PtSessionWrap->ptsession->cookies);

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