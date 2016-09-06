#include "DirectorywrapAsynchro.h"
#include"SessionwrapAsynchro.h"
#include"ControleDirectoryAsynchro.h"
#include"Directory.h"
#include"DataControle.h"
#include"Session.h"
#include"Utility.h"
#include"Work.h"
#include<vector>
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
using v8::Array;
using namespace v8;
using namespace WaDirectory;
using namespace std;

namespace WaDirectorywrapAsynchro_data_v8 {
Persistent<Function> DirectorywrapAsynchro::constructor;
Persistent<Value> DirectorywrapAsynchro::prototype_Directory_Synchrone;


Local<Boolean> DirectorywrapAsynchro::ControleDirectoryUnwrap(Local<Object> handle, Isolate* isolate)
{
	EscapableHandleScope scope(isolate);

	if (!handle.IsEmpty() && handle->InternalFieldCount() == 1) {

		Local<Value> Pt_Prototype = handle->GetPrototype();
		Utility util;

		if (Pt_Prototype == prototype_Directory_Synchrone) {
			Local<Boolean> Resultat = Boolean::New(isolate, true);
			return scope.Escape(Resultat);

		}


	}
	Local<Boolean> Resultat = Boolean::New(isolate, false);
	return scope.Escape(Resultat);
}
DirectorywrapAsynchro::DirectorywrapAsynchro() :ptdirectory() {

}

DirectorywrapAsynchro::~DirectorywrapAsynchro() {
}



void DirectorywrapAsynchro::Init(Local<Object> exports) {

	Isolate* isolate = exports->GetIsolate();

	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);

	tpl->SetClassName(String::NewFromUtf8(isolate, "DirectorywrapAsynchro"));
  
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
  
	NODE_SET_PROTOTYPE_METHOD(tpl, "LogInAsynchro", LogInAsynchro);

	NODE_SET_PROTOTYPE_METHOD(tpl, "GetGroupwrapNamesAsynchro", GetGroupwrapNamesAsynchro);

	NODE_SET_PROTOTYPE_METHOD(tpl, "GetGroupwrapAsynchro", GetGroupwrapAsynchro);

	NODE_SET_PROTOTYPE_METHOD(tpl, "GetUserwrapAsynchro", GetUserwrapAsynchro);

	NODE_SET_PROTOTYPE_METHOD(tpl, "GetSessionwrapAsynchro", GetSessionwrapAsynchro);

	NODE_SET_PROTOTYPE_METHOD(tpl, "UserwrapBelongToAsynchro", UserwrapBelongToAsynchro);

	NODE_SET_PROTOTYPE_METHOD(tpl, "LogOutAsynchro", LogOutAsynchro);

	NODE_SET_PROTOTYPE_METHOD(tpl, "GetGroupwrapIDAsynchro", GetGroupwrapIDAsynchro);
  

  
	constructor.Reset(isolate, tpl->GetFunction());
  
	exports->Set(String::NewFromUtf8(isolate, "DirectorywrapAsynchro"),
               tpl->GetFunction());
}

void DirectorywrapAsynchro::New(const FunctionCallbackInfo<Value>& args) {



	Isolate* isolate = args.GetIsolate();

	std::string Message;

	if ((args.Length() == 2) )
	{

		/*
		Traitement du cas Directorywrap Dir=new Directorywrap(Url_Wakanda, Url_Directory) ;
		*/

	
	    if ((args[0]->IsString()) && (args[1]->IsString()))
		{


			Utility util;

			std::string Url_Wakanda = util.V8Utf8ValueToStdString(args[0]);

			std::string Url_Directory = util.V8Utf8ValueToStdString(args[1]);

			DirectorywrapAsynchro* Obj_Directory_Wrap = new DirectorywrapAsynchro();

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



void DirectorywrapAsynchro::LogInAsynchro(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	
	ControleDirectoryAsynchro* PtControleDirectoryAsynchro = new ControleDirectoryAsynchro();
	
	bool controle = false;
	
	std::string Message;
	
	vector<DataControle>* Pt_Vector=PtControleDirectoryAsynchro->ControleLogInAsynchro(args, controle, Message);
	
	if (controle == true)
	{
		
		Work *work = new Work();

		work->request.data = work;

		DataControle Directorydata = Pt_Vector->at(0);

		DirectorywrapAsynchro* PtDirectorywrapAsynchro = Directorydata.Output.PtDirectorywrapAsynchro;

		Thread_Data Pt_DirectoryWrapAsynchro_Intra;

		Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

		work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);
		
		DataControle Userdata = Pt_Vector->at(1);

		UserwrapAsynchro* PtUserWrap = Userdata.Output.PtUserwrapAsynchro;;

		Utility util;

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

		uv_queue_work(uv_default_loop(), &work->request, LogInAsynchroWork, LogInAsynchroWorkComplete);

		args.GetReturnValue().Set(Undefined(isolate));
	
	}

	else
	{

		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
		args.GetReturnValue().SetUndefined();

	}


}
void DirectorywrapAsynchro::LogInAsynchroWork(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);

	string user = work->Input_Data[0].Argument.user;

	string password = work->Input_Data[1].Argument.password;

	Thread_Data Pt_SessionWrapAsynchro_Intra;

	Pt_SessionWrapAsynchro_Intra.Argument.PtSession = work->Intra_Data[0].Argument.PtDirectorywrapAsynchro->ptdirectory->LogIn(user, password);

	work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);
}
void DirectorywrapAsynchro::LogInAsynchroWorkComplete(uv_work_t  *request, int status)
{
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	ISession *PtSession = work->Intra_Data[1].Argument.PtSession;

	Local<Object> ObjectSessionwrapAsynchro = SessionwrapAsynchro::CreateSessionwrapAsynchro(isolate, PtSession, work->Intra_Data[0].Argument.PtDirectorywrapAsynchro);

	Handle<Value> args[] = { Null(isolate), ObjectSessionwrapAsynchro };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;
}

void DirectorywrapAsynchro::GetGroupwrapIDAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args)
{

	Isolate* isolate = args.GetIsolate();

	ControleDirectoryAsynchro* PtControleDirectoryAsynchro = new ControleDirectoryAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleDirectoryAsynchro->ControleGetGroupwrapIDAsynchro(args, controle, Message);

	if (controle == true)
	{

		Work *work = new Work();

		work->request.data = work;

		DataControle Directorydata = Pt_Vector->at(0);

		DirectorywrapAsynchro* PtDirectorywrapAsynchro = Directorydata.Output.PtDirectorywrapAsynchro;


		Thread_Data Pt_DirectoryWrapAsynchro_Intra;

		Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

		Local<Function> commeback = Local<Function>::Cast(args[0]);

		work->callback.Reset(isolate, commeback);

		work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

		uv_queue_work(uv_default_loop(), &work->request, GetGroupwrapIDAsynchroWork, GetGroupwrapIDAsynchroWorkComplete);

		args.GetReturnValue().Set(Undefined(isolate));


	}
	
	else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetNull();

		}
	


}
void DirectorywrapAsynchro::GetGroupwrapIDAsynchroWork(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);

	std::vector<std::string> Vector;

	work->Intra_Data[0].Argument.PtDirectorywrapAsynchro->ptdirectory->GetGroupId(Vector);

	work->liste = Vector;

}
void DirectorywrapAsynchro::GetGroupwrapIDAsynchroWorkComplete(uv_work_t  *request, int status)
{
	Isolate* isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Utility util;

	Work *work = (Work*)(request->data);

	std::vector<std::string> Vector = work->liste;

	Local<Array> Resulat = util.StdVectorToV8Array(isolate, Vector);

	Handle<Value> args[] = { Null(isolate), Resulat };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;
}

void DirectorywrapAsynchro::GetGroupwrapNamesAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args)
{

    Isolate* isolate = args.GetIsolate();

	ControleDirectoryAsynchro* PtControleDirectoryAsynchro = new ControleDirectoryAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleDirectoryAsynchro->ControleGetGroupwrapNamesAsynchro(args, controle, Message);

	if (controle == true)
	{

		Work *work = new Work();

		work->request.data = work;

		DataControle Directorydata = Pt_Vector->at(0);

		DirectorywrapAsynchro* PtDirectorywrapAsynchro = Directorydata.Output.PtDirectorywrapAsynchro;

		Thread_Data Pt_DirectoryWrapAsynchro_Intra;

		Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

		Local<Function> commeback = Local<Function>::Cast(args[0]);

		work->callback.Reset(isolate, commeback);

		work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

		uv_queue_work(uv_default_loop(), &work->request, GetGroupwrapNamesAsynchroWork, GetGroupwrapNamesAsynchroWorkComplete);

		args.GetReturnValue().Set(Undefined(isolate));


	}
	else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetNull();

		}
	


}
void DirectorywrapAsynchro::GetGroupwrapNamesAsynchroWork(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);

	std::vector<std::string> Vector;

	work->Intra_Data[0].Argument.PtDirectorywrapAsynchro->ptdirectory->GetGroupNames(Vector);

	work->liste = Vector;

}
void DirectorywrapAsynchro::GetGroupwrapNamesAsynchroWorkComplete(uv_work_t  *request, int status)
{
	Isolate* isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Utility util;

	Work *work = (Work*)(request->data);

	std::vector<std::string> Vector = work->liste;

	Local<Array> Resulat = util.StdVectorToV8Array(isolate, Vector);

	Handle<Value> args[] = { Null(isolate), Resulat };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;
}
void DirectorywrapAsynchro::GetGroupwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args)
{

	Isolate* isolate = args.GetIsolate();

	ControleDirectoryAsynchro* PtControleDirectoryAsynchro = new ControleDirectoryAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleDirectoryAsynchro->ControleGetGroupwrapAsynchro(args, controle, Message);

	if (controle == true)
	{
		Work *work = new Work();

		work->request.data = work;

		DataControle Directorydata = Pt_Vector->at(0);

		DirectorywrapAsynchro* PtDirectorywrapAsynchro = Directorydata.Output.PtDirectorywrapAsynchro;

		Thread_Data Pt_DirectoryWrapAsynchro_Intra;

		Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

		work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

		DataControle Idgroupdata = Pt_Vector->at(1);

		Thread_Data Pt_GroupId;

		Pt_GroupId.Argument.GroupId = Idgroupdata.Output.GroupId;

		work->Input_Data.push_back(Pt_GroupId);

		Local<Function> commeback = Local<Function>::Cast(args[1]);

		work->callback.Reset(isolate, commeback);

		uv_queue_work(uv_default_loop(), &work->request, GetGroupwrapAsynchroWork, GetGroupwrapAsynchroWorkComplete);

		args.GetReturnValue().Set(Undefined(isolate));

	}

	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
		args.GetReturnValue().SetNull();

	}
}
void DirectorywrapAsynchro::GetGroupwrapAsynchroWork(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);

	string GroupId = work->Input_Data[0].Argument.GroupId;


	Thread_Data Pt_GroupWrapAsynchro_Intra;

	Pt_GroupWrapAsynchro_Intra.Argument.PtGroup = work->Intra_Data[0].Argument.PtDirectorywrapAsynchro->ptdirectory->GetGroup(GroupId);

	work->Intra_Data.push_back(Pt_GroupWrapAsynchro_Intra);


}
void DirectorywrapAsynchro::GetGroupwrapAsynchroWorkComplete(uv_work_t  *request, int status)
{

	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	IGroup *PtGroup = work->Intra_Data[1].Argument.PtGroup;

	Local<Object> ObjectGroupwrapAsynchro = GroupwrapAsynchro::CreateGroupwrapAsynchro(isolate, PtGroup, work->Intra_Data[0].Argument.PtDirectorywrapAsynchro);

	Handle<Value> args[] = { Null(isolate), ObjectGroupwrapAsynchro };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;


}
void DirectorywrapAsynchro::GetUserwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();

	ControleDirectoryAsynchro* PtControleDirectoryAsynchro = new ControleDirectoryAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleDirectoryAsynchro->ControleGetUserwrapAsynchro(args, controle, Message);

	if (controle == true)
	{
	
		Work *work = new Work();

		work->request.data = work;

		DataControle Directorydata = Pt_Vector->at(0);

		DirectorywrapAsynchro* PtDirectorywrapAsynchro = Directorydata.Output.PtDirectorywrapAsynchro;

		Thread_Data Pt_DirectoryWrapAsynchro_Intra;

		Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

		work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

		DataControle IdUserdata = Pt_Vector->at(1);

		Thread_Data Pt_UserId;

		Pt_UserId.Argument.user = IdUserdata.Output.UserId;

		work->Input_Data.push_back(Pt_UserId);

		DataControle IdPassworddata = Pt_Vector->at(2);

		Thread_Data Pt_PasswordId;

		Pt_PasswordId.Argument.password = IdPassworddata.Output.Password;

		work->Input_Data.push_back(Pt_PasswordId);

		Local<Function> commeback = Local<Function>::Cast(args[2]);

		work->callback.Reset(isolate, commeback);

		uv_queue_work(uv_default_loop(), &work->request, GetUserwrapAsynchroWork, GetUserwrapAsynchroWorkComplete);

		args.GetReturnValue().Set(Undefined(isolate));


	
	}


	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
		args.GetReturnValue().SetNull();
	}

}
void DirectorywrapAsynchro::GetUserwrapAsynchroWork(uv_work_t  *request){

	Work *work = (Work*)(request->data);

	string UserId = work->Input_Data[0].Argument.user;

	string Password = work->Input_Data[1].Argument.password;

	Thread_Data Pt_UserWrapAsynchro_Intra;

	bool resultat = false;

	resultat = work->Intra_Data[0].Argument.PtDirectorywrapAsynchro->ptdirectory->Existbyname(UserId);

	resultat = work->Intra_Data[0].Argument.PtDirectorywrapAsynchro->ptdirectory->Isvalid(UserId, Password);

	Pt_UserWrapAsynchro_Intra.Argument.Ptuser = NULL;

	if (resultat)
	{
	
		Pt_UserWrapAsynchro_Intra.Argument.Ptuser = work->Intra_Data[0].Argument.PtDirectorywrapAsynchro->ptdirectory->GetUser(UserId, Password);
		
	}
	

	work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

}
void DirectorywrapAsynchro::GetUserwrapAsynchroWorkComplete(uv_work_t  *request, int status){
	
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	IUser *PtUser = work->Intra_Data[1].Argument.Ptuser;

	Local<Object> ObjectUserwrapAsynchro = UserwrapAsynchro::CreateUserWrapAsynchro(isolate, PtUser, work->Intra_Data[0].Argument.PtDirectorywrapAsynchro);

	Handle<Value> args[] = { Null(isolate), ObjectUserwrapAsynchro };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}
void DirectorywrapAsynchro::GetSessionwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){

	Isolate* isolate = args.GetIsolate();


	ControleDirectoryAsynchro* PtControleDirectoryAsynchro = new ControleDirectoryAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleDirectoryAsynchro->ControleGetSessionwrapAsynchro(args, controle, Message);

	if (controle == true)
	{
		Work *work = new Work();

		work->request.data = work;

		DataControle Directorydata = Pt_Vector->at(0);

		DirectorywrapAsynchro* PtDirectorywrapAsynchro = Directorydata.Output.PtDirectorywrapAsynchro;

		Thread_Data Pt_DirectoryWrapAsynchro_Intra;

		Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

		work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

		DataControle IdSessiondata = Pt_Vector->at(1);

		Thread_Data Pt_SessionId;

		Pt_SessionId.Argument.SessionId = IdSessiondata.Output.SessionId;

		work->Input_Data.push_back(Pt_SessionId);

		Local<Function> commeback = Local<Function>::Cast(args[1]);

		work->callback.Reset(isolate, commeback);

		uv_queue_work(uv_default_loop(), &work->request, GetSessionwrapAsynchroWork, GetSessionwrapAsynchroWorkComplete);

		args.GetReturnValue().Set(Undefined(isolate));
	}

	else{

			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetNull();

		}
	

}
void DirectorywrapAsynchro::GetSessionwrapAsynchroWork(uv_work_t  *request){

	Work *work = (Work*)(request->data);

	string SessionId = work->Input_Data[0].Argument.SessionId;

	Thread_Data Pt_SessionWrapAsynchro_Intra;

	Pt_SessionWrapAsynchro_Intra.Argument.PtSession = work->Intra_Data[0].Argument.PtDirectorywrapAsynchro->ptdirectory->GetSession(SessionId);

	work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);

}
void DirectorywrapAsynchro::GetSessionwrapAsynchroWorkComplete(uv_work_t  *request, int status){
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	ISession *PtSession = work->Intra_Data[1].Argument.PtSession;

	Local<Object> ObjectSessionwrapAsynchro = SessionwrapAsynchro::CreateSessionwrapAsynchro(isolate, PtSession, work->Intra_Data[0].Argument.PtDirectorywrapAsynchro);

	Handle<Value> args[] = { Null(isolate), ObjectSessionwrapAsynchro };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}

void DirectorywrapAsynchro::UserwrapBelongToAsynchro(const FunctionCallbackInfo<Value>& args) {



	Isolate* isolate = args.GetIsolate();

	bool Resultat = false;

	ControleDirectoryAsynchro* PtControleDirectoryAsynchro = new ControleDirectoryAsynchro();

	bool controle = false;

	std::string Message;
	int Methode = 0;

	vector<DataControle>* Pt_Vector = PtControleDirectoryAsynchro->ControleUserwrapBelongToAsynchro(args, controle, Message, Methode);

	if (controle == true)
	{
		Work *work = new Work();

		work->request.data = work;

		DataControle Directorydata = Pt_Vector->at(0);

		DirectorywrapAsynchro* PtDirectorywrapAsynchro = Directorydata.Output.PtDirectorywrapAsynchro;

		Thread_Data Pt_DirectoryWrapAsynchro_Intra;

		Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

		work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);
		if (Methode == 1)
		{
			DataControle Userdata = Pt_Vector->at(1);

			UserwrapAsynchro* PtUserWrapAsynchro = Userdata.Output.PtUserwrapAsynchro;

			Thread_Data Pt_UserWrapAsynchro_Intra;

			Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

			work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

			DataControle GroupIddata = Pt_Vector->at(2);

			Thread_Data Pt_inGroupID;

			Pt_inGroupID.Argument.GroupId = GroupIddata.Output.GroupId;

			work->Input_Data.push_back(Pt_inGroupID);

			Local<Function> commeback = Local<Function>::Cast(args[2]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, UserwrapBelongAsynchroWorkTo_2, UserwrapBelongAsynchroWorkCompleteTo_2);

			args.GetReturnValue().Set(Undefined(isolate));

		}
		if (Methode == 2)
		{
			DataControle Userdata = Pt_Vector->at(1);

			UserwrapAsynchro* PtUserWrapAsynchro = Userdata.Output.PtUserwrapAsynchro;

			Thread_Data Pt_UserWrapAsynchro_Intra;

			Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

			work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

			DataControle Groupdata = Pt_Vector->at(2);

			GroupwrapAsynchro* PtGroupWrapAsynchro = Groupdata.Output.PtGroupwrapAsynchro;

			Thread_Data Pt_GroupWrapAsynchro_Intra;

			Pt_GroupWrapAsynchro_Intra.Argument.PtGroupWrapAsynchro = PtGroupWrapAsynchro;

			work->Intra_Data.push_back(Pt_GroupWrapAsynchro_Intra);


			Local<Function> commeback = Local<Function>::Cast(args[2]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, UserwrapBelongAsynchroWorkTo_3, UserwrapBelongAsynchroWorkCompleteTo_3);

			args.GetReturnValue().Set(Undefined(isolate));
		}
		if (Methode == 3)
		{
			DataControle Sessiondata = Pt_Vector->at(1);

			SessionwrapAsynchro* PtSessionWrapAsynchro = Sessiondata.Output.PtSessionwrapAsynchro;

			Thread_Data Pt_SessionWrapAsynchro_Intra;

			Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

			work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);

			DataControle GroupIddata = Pt_Vector->at(2);

			Thread_Data Pt_inGroupID;

			Pt_inGroupID.Argument.GroupId = GroupIddata.Output.GroupId;

			work->Input_Data.push_back(Pt_inGroupID);

			Local<Function> commeback = Local<Function>::Cast(args[2]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, UserwrapBelongAsynchroWorkTo_1, UserwrapBelongAsynchroWorkCompleteTo_1);

			args.GetReturnValue().Set(Undefined(isolate));
		}

	}

	

	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of argument")));

		args.GetReturnValue().SetUndefined();
	}
}

void DirectorywrapAsynchro::UserwrapBelongAsynchroWorkTo_1(uv_work_t  *request){

    Work *work = (Work*)(request->data);

	string GroupId = work->Input_Data[0].Argument.GroupId;

	SessionwrapAsynchro* PtSessionWrapAsynchro = work->Intra_Data[1].Argument.ptSessionwrapAsynchro;

	Thread_Data Resultat_Intra;

	Resultat_Intra.Argument.Resultat = work->Intra_Data[0].Argument.PtDirectorywrapAsynchro->ptdirectory->UserBelongTo(PtSessionWrapAsynchro->ptsession,GroupId);

	work->Intra_Data.push_back(Resultat_Intra);

}
void DirectorywrapAsynchro::UserwrapBelongAsynchroWorkCompleteTo_1(uv_work_t  *request, int status){
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

void DirectorywrapAsynchro::UserwrapBelongAsynchroWorkTo_2(uv_work_t  *request){

	Work *work = (Work*)(request->data);

	string GroupId = work->Input_Data[0].Argument.GroupId;

	UserwrapAsynchro* PtUserWrapAsynchro = work->Intra_Data[1].Argument.PtUserwrapAsynchro;

	Thread_Data Resultat_Intra;

	Resultat_Intra.Argument.Resultat = work->Intra_Data[0].Argument.PtDirectorywrapAsynchro->ptdirectory->UserBelongTo(PtUserWrapAsynchro->ptuser, GroupId);

	work->Intra_Data.push_back(Resultat_Intra);

}
void DirectorywrapAsynchro::UserwrapBelongAsynchroWorkCompleteTo_2(uv_work_t  *request, int status){
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

void DirectorywrapAsynchro::UserwrapBelongAsynchroWorkTo_3(uv_work_t  *request){

	Work *work = (Work*)(request->data);

	GroupwrapAsynchro* PtGroupWrapAsynchro =  work->Intra_Data[2].Argument.PtGroupWrapAsynchro;

	UserwrapAsynchro* PtUserWrapAsynchro = work->Intra_Data[1].Argument.PtUserwrapAsynchro;

	Thread_Data Resultat_Intra;

	Resultat_Intra.Argument.Resultat = work->Intra_Data[0].Argument.PtDirectorywrapAsynchro->ptdirectory->UserBelongTo(PtUserWrapAsynchro->ptuser, PtGroupWrapAsynchro->ptgroup);

	work->Intra_Data.push_back(Resultat_Intra);

}
void DirectorywrapAsynchro::UserwrapBelongAsynchroWorkCompleteTo_3(uv_work_t  *request, int status){

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
void DirectorywrapAsynchro::LogOutAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args)
{

	Isolate* isolate = args.GetIsolate();

	ControleDirectoryAsynchro* PtControleDirectoryAsynchro = new ControleDirectoryAsynchro();

	bool controle = false;

	std::string Message;

	vector<DataControle>* Pt_Vector = PtControleDirectoryAsynchro->ControleLogOutAsynchro1(args, controle, Message);

	if (controle == true)
	{

		Work *work = new Work();

		work->request.data = work;

		DataControle Directorydata = Pt_Vector->at(0);

		DirectorywrapAsynchro* PtDirectorywrapAsynchro = Directorydata.Output.PtDirectorywrapAsynchro;

		Thread_Data Pt_DirectoryWrapAsynchro_Intra;

		Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

		work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

		DataControle Sessiondata = Pt_Vector->at(1);

		SessionwrapAsynchro* PtSessionWrapAsynchro = Sessiondata.Output.PtSessionwrapAsynchro;

		Thread_Data Pt_SessionWrapAsynchro_Intra;

		Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

		work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);

		Local<Function> commeback = Local<Function>::Cast(args[1]);

		work->callback.Reset(isolate, commeback);

		uv_queue_work(uv_default_loop(), &work->request, LogOutAsynchroWork, LogOutAsynchroWorkComplete);

		args.GetReturnValue().Set(Undefined(isolate));
	}

	else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetUndefined();
		}

	

}
void DirectorywrapAsynchro::LogOutAsynchroWork(uv_work_t  *request)
{
	Work *work = (Work*)(request->data);

	SessionwrapAsynchro* PtSessionWrapAsynchro = work->Intra_Data[1].Argument.ptSessionwrapAsynchro;

	Thread_Data Resultat_Intra;

	Resultat_Intra.Argument.Resultat = work->Intra_Data[0].Argument.PtDirectorywrapAsynchro->ptdirectory->LogOut(PtSessionWrapAsynchro->ptsession);

	work->Intra_Data.push_back(Resultat_Intra);

}
void DirectorywrapAsynchro::LogOutAsynchroWorkComplete(uv_work_t  *request, int status)
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

} 