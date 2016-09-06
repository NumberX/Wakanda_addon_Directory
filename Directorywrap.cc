#include "Directorywrap.h"
#include"Sessionwrap.h"
#include"Directory.h"
#include"Work.h"
#include"Session.h"
#include"Utility.h"
#include"ControleDirectorysynchro.h"
#include<vector>
#include<string>
#include<iostream>
using v8::Exception;
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
using namespace WaDirectorywrapAsynchro_data_v8;
namespace WaDirectorywrap_data_v8 {
Persistent<Function> Directorywrap::constructor;

Persistent<Value> Directorywrap::prototype_Directory_Synchrone;


Local<Boolean> Directorywrap::ControleDirectoryUnwrap(Local<Object> handle, Isolate* isolate)
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

			 
				  Utility util;

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

	bool controle = false;

	std::string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleDirectorysynchro->ControleLogInsynchro(args, controle, Message);
	if (controle == true)
	{
		DataControlesyn Directorydata = Pt_Vector->at(0);

		Directorywrap* PtDirectoryWrap = Directorydata.Output.PtDirectorywrap;

		DataControlesyn Userdata = Pt_Vector->at(1);

		Userwrap* PtUserWrap = Userdata.Output.PtUserwrap;

		Utility util;

		string user = PtUserWrap->ptuser->Username;

		string password = PtUserWrap->ptuser->Password;

		ISession *PtSession = PtDirectoryWrap->ptdirectory->LogIn(user, password);

		if (PtSession != NULL)
		{

			Local<Object> ObjectSessionWrap = Sessionwrap::CreateSessionWrap(isolate, PtSession, PtDirectoryWrap);

			args.GetReturnValue().Set(ObjectSessionWrap);
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

		Utility util;

		Local<Array> Resulat = util.StdVectorToV8Array(isolate, Vector);

		args.GetReturnValue().Set(Resulat);
	}

	else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetNull();

		}
	
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

		Utility util;

		Local<Array> Resulat = util.StdVectorToV8Array(isolate, Vector);

		args.GetReturnValue().Set(Resulat);
	}

	else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetNull();

		}
	
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
	
}
void Directorywrap::GetSessionwrap(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	ControleDirectorysynchro *PtControleDirectorysynchro = new ControleDirectorysynchro();

	bool controle = false;

	std::string Message;

	vector<DataControlesyn>* Pt_Vector = PtControleDirectorysynchro->ControleGetSessionwrapsynchro(args, controle, Message);
	if (controle == true)
	{
		DataControlesyn Directorydata = Pt_Vector->at(0);

		Directorywrap* PtDirectoryWrap = Directorydata.Output.PtDirectorywrap;

		DataControlesyn SessionIddata = Pt_Vector->at(1);

		string SessionId = SessionIddata.Output.SessionId;

		ISession* PtSession = PtDirectoryWrap->ptdirectory->GetSession(SessionId);

		Local<Object> ObjectUserWrap = Sessionwrap::CreateSessionWrap(isolate, PtSession, PtDirectoryWrap);

		args.GetReturnValue().Set(ObjectUserWrap);
	}
else{

			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetNull();

		}
	
	
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
		DataControlesyn Directorydata = Pt_Vector->at(0);

		Directorywrap* PtDirectoryWrap = Directorydata.Output.PtDirectorywrap;

		bool Resultat = false;

		if (Methode == 1)
		{
			DataControlesyn Userdata = Pt_Vector->at(1);

			Userwrap* PtUserWrap = Userdata.Output.PtUserwrap;

			DataControlesyn GroupIddata = Pt_Vector->at(2);

			string inGroupID = GroupIddata.Output.GroupId;

			Resultat = PtDirectoryWrap->ptdirectory->UserBelongTo(PtUserWrap->ptuser, inGroupID);

			args.GetReturnValue().Set(Boolean::New(isolate, Resultat));
		}
		if (Methode == 2)
		{
			DataControlesyn Userdata = Pt_Vector->at(1);

			Userwrap* PtUserWrap = Userdata.Output.PtUserwrap;

			DataControlesyn Groupdata = Pt_Vector->at(2);

			Groupwrap* PtGroupWrap = Userdata.Output.PtGroupwrap;

			Resultat = PtDirectoryWrap->ptdirectory->UserBelongTo(PtUserWrap->ptuser, PtGroupWrap->ptgroup);

			args.GetReturnValue().Set(Boolean::New(isolate, Resultat));

		}
		if (Methode == 3)
		{
			DataControlesyn Sessiondata = Pt_Vector->at(1);

			Sessionwrap* PtSessionWrap = Sessiondata.Output.PtSessionwrap;

			DataControlesyn GroupIddata = Pt_Vector->at(2);

			string inGroupID = GroupIddata.Output.GroupId;

			Resultat = PtDirectoryWrap->ptdirectory->UserBelongTo(PtSessionWrap->GetSession(), inGroupID);

			args.GetReturnValue().Set(Boolean::New(isolate, Resultat));
		}
	}

	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

		args.GetReturnValue().SetUndefined();
	}
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

	
}


} 