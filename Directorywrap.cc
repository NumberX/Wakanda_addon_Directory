#include "Directorywrap.h"
#include"Sessionwrap.h"
#include"Directory.h"
#include"Work.h"
#include"Session.h"
#include"Utility.h"
#include"ControleDirectory.h"
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
using namespace Controle;
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

  ControleDirectory* PtControleDirectory = new ControleDirectory();
  
  std::string Message;
  
if ((args.Length() == 2) || (args.Length() == 1) )
  {

		  /*
		  Traitement du cas Directorywrap Dir=new Directorywrap(Url_Wakanda, Url_Directory) ;
		  */
	 
	  if (args.Length() == 1) {


		  Directorywrap* PtDirectoryWrap = new Directorywrap();

		  PtDirectoryWrap->Wrap(args.This());

		  prototype_Directory_Synchrone.Reset(isolate, args.This()->GetPrototype());

		  args.GetReturnValue().Set(args.Holder());
	 
	  }
		  else if ((args[0]->IsString())&&(args[1]->IsString()))
		  { 

			 
				  Utility util;

				  std::string Url_Wakanda = util.V8Utf8ValueToStdString(args[0]);

				  std::string Url_Directory = util.V8Utf8ValueToStdString(args[1]);

				  Directorywrap* Obj_Directory_Wrap = new Directorywrap();

				  Directory *Pt_Directory = new Directory(Url_Wakanda, Url_Directory);

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

	string Message;
	
	ControleDirectory* ContDirectory = new ControleDirectory();

	
	if (ControleDirectoryUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false) {

		
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"this is not a Directory object")));
	    args.GetReturnValue().SetUndefined();
	}
	else
	{ 
		Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());
		
		bool Resultat = ContDirectory->ControleGetLenght(args, Message, 1);
		
	if (Resultat == true)
	{
		
		if (Userwrap::ControleUserUnwrap(args[0]->ToObject(), isolate)->BooleanValue() == true)
		{ 
		Userwrap* PtUserWrap = ObjectWrap::Unwrap<Userwrap>(args[0]->ToObject());

		Utility util;

		string user = PtUserWrap->ptuser->Username; 

		string password = PtUserWrap->ptuser->Password;
		
		ISession *PtSession = PtDirectoryWrap->ptdirectory->LogIn(user, password);

		if (PtSession !=NULL)
		{ 
			
		Local<Object> ObjectSessionWrap = Sessionwrap::CreateSessionWrap(isolate, PtSession,PtDirectoryWrap);

		args.GetReturnValue().Set(ObjectSessionWrap);
		}

	
		else
		{

		args.GetReturnValue().SetNull();
		}
		}
		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "the argument need to be Userobject")));
			args.GetReturnValue().SetUndefined();

		}

	
	}
	else
	{

		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
		args.GetReturnValue().SetUndefined();

	}
	}


}
void Directorywrap::GetGroupwrapID(const v8::FunctionCallbackInfo<v8::Value>& args)
{

	Isolate* isolate = args.GetIsolate();

	ControleDirectory* ContDirectory = new ControleDirectory();

	if (ControleDirectoryUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false) {


		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a Directory object")));
		args.GetReturnValue().SetUndefined();
	}
	else
	{
		Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());


		string Message;

		bool Resultat = ContDirectory->ControleGetGroupwrapNames(args, PtDirectoryWrap->GetDirectory(), Message);

		if (Resultat == true)
		{

			std::vector<std::string> Vector;

			PtDirectoryWrap->ptdirectory->GetGroupId(Vector);

			Utility util;

			Local<Array> Resulat = util.StdVectorToV8Array(isolate, Vector);

			args.GetReturnValue().Set(Resulat);


		}
		else
		{
			//isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetNull();

		}
	}
}
void Directorywrap::GetGroupwrapNames(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	ControleDirectory* ContDirectory = new ControleDirectory();

	if (ControleDirectoryUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false) {


		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a Directory object")));
		args.GetReturnValue().SetUndefined();
	}
	else
	{
		Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());


		string Message;

		bool Resultat = ContDirectory->ControleGetGroupwrapNames(args, PtDirectoryWrap->GetDirectory(), Message);

		if (Resultat == true)
		{

			std::vector<std::string> Vector;

			PtDirectoryWrap->ptdirectory->GetGroupNames(Vector);

			Utility util;

			Local<Array> Resulat = util.StdVectorToV8Array(isolate, Vector);

			args.GetReturnValue().Set(Resulat);


		}
		else
		{
			//isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetNull();

		}
	}
}
void Directorywrap::GetGroupwrap(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();
	
	ControleDirectory* ContDirectory = new ControleDirectory();

	if (ControleDirectoryUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false) {


		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a Directory object")));
		args.GetReturnValue().SetUndefined();
	}
	else
	{
		Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

		string Message;


		bool Resultat = ContDirectory->ControleGetGroupwrap(args, PtDirectoryWrap->GetDirectory(), Message);

		if (Resultat == true)
		{

			Utility util;

			string GroupId = util.V8Utf8ValueToStdString(args[0]);

			IGroup* PtGroup = PtDirectoryWrap->ptdirectory->GetGroup(GroupId);

			if (PtGroup != NULL)
			{ 

			Local<Object> ObjectGroupWrap = Groupwrap::CreateGroupWrap(isolate, PtGroup, PtDirectoryWrap);

			args.GetReturnValue().Set(ObjectGroupWrap);
			}
			else
			{
		//		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a GroupId")));
				args.GetReturnValue().SetNull();
			}
		}
		else{

			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetUndefined();
		}
	}
	
}
void Directorywrap::GetUserwrap(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	ControleDirectory* ContDirectory = new ControleDirectory();

	if (ControleDirectoryUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false) {


		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a Directory object")));
		args.GetReturnValue().SetUndefined();
	}
	else
	{
		Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

		string Message;

		bool Resultat =  ContDirectory->ControleGetUserwrap(args, PtDirectoryWrap->GetDirectory(), Message);

		if (Resultat == true)
		{

			Utility util;

			string UserId = util.V8Utf8ValueToStdString(args[0]);
			
			string Password = util.V8Utf8ValueToStdString(args[1]);
			
			bool resultat=false;

			resultat= PtDirectoryWrap->ptdirectory->Existbyname(UserId);
	        
			resultat = PtDirectoryWrap->ptdirectory->Isvalid(UserId, Password);
			
			
			IUser* PtUser = NULL;
			if (resultat)
			{ 
				PtUser =  PtDirectoryWrap->ptdirectory->GetUser(UserId, Password);

			
			}
			if (PtUser)
			{
				
				Local<Object> ObjectUserWrap = Userwrap::CreateUserWrap(isolate, PtUser, PtDirectoryWrap);

				
				args.GetReturnValue().Set(ObjectUserWrap);
			}
			else
			{
			//	isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a UserId")));
				args.GetReturnValue().SetNull();
			}

		}

		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetUndefined();
		}
	}
}
void Directorywrap::GetSessionwrap(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	ControleDirectory* ContDirectory = new ControleDirectory();

	if (ControleDirectoryUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false) {


		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a Directory object")));
		args.GetReturnValue().SetUndefined();
	}
	else
	{
		Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());
		string Message;


		bool Resultat = ContDirectory->ControleGetSessionwrap(args, PtDirectoryWrap->GetDirectory(), Message);

		if (Resultat == true)
		{
			Utility util;

			string SessionId = util.V8Utf8ValueToStdString(args[0]);

			ISession* PtSession = PtDirectoryWrap->ptdirectory->GetSession(SessionId);

			Local<Object> ObjectUserWrap = Sessionwrap::CreateSessionWrap(isolate, PtSession, PtDirectoryWrap);

			args.GetReturnValue().Set(ObjectUserWrap);

		}

		else{

			//isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));
			args.GetReturnValue().SetNull();

		}
	}
	
}
void Directorywrap::UserwrapBelongTo(const FunctionCallbackInfo<Value>& args) {

	bool Resultat = false;

	ControleDirectory *ConDirec;

	ConDirec = new ControleDirectory();

	std::string Message;

	Isolate* isolate = args.GetIsolate();
	if (args.Length()==2)
	{ 

		if (ControleDirectoryUnwrap(args.Holder(), isolate)->BooleanValue() == true)

		{ 
	
			Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());
	
			if ((Userwrap::ControleUserUnwrap(args[0]->ToObject(), isolate)->BooleanValue() == true) || (Sessionwrap::ControleSessionUnwrap(args[0]->ToObject(), isolate)->BooleanValue() == true))
	
			{ 
	
	
				if (Userwrap::ControleUserUnwrap(args[0]->ToObject(), isolate)->BooleanValue() == true)
	
				{ 
					
		
					if (ConDirec->ControleGetType(args,Message,1))
					{
			
						

						Utility util;
			
						string inGroupID = util.V8Utf8ValueToStdString(args[1]);

						Userwrap* PtUserWrap = ObjectWrap::Unwrap<Userwrap>(args[0]->ToObject());

						Resultat = PtDirectoryWrap->ptdirectory->UserBelongTo(PtUserWrap->ptuser, inGroupID);
					
						args.GetReturnValue().Set(Boolean::New(isolate, Resultat));
		
					}
			
					else if (Groupwrap::ControleGroupUnwrap(args[1]->ToObject(), isolate)->BooleanValue() == true)
					{
		
						Groupwrap* PtGroupWrap = ObjectWrap::Unwrap<Groupwrap>(args[1]->ToObject());

						Userwrap* PtUserWrap = ObjectWrap::Unwrap<Userwrap>(args[0]->ToObject());

						Resultat = PtDirectoryWrap->ptdirectory->UserBelongTo(PtUserWrap->ptuser, PtGroupWrap->ptgroup);

						args.GetReturnValue().Set(Boolean::New(isolate, Resultat));

					}
					else
					{
						isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong argument ")));

						args.GetReturnValue().SetUndefined();
					}
	
				}
				if (Sessionwrap::ControleSessionUnwrap(args[0]->ToObject(), isolate)->BooleanValue() == true)
	
				{
					if (ConDirec->ControleGetType(args,  Message, 1))
					{

						Utility util;

						string inGroupID = util.V8Utf8ValueToStdString(args[1]);

						Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args[0]->ToObject());

						Resultat = PtDirectoryWrap->ptdirectory->UserBelongTo(PtSessionWrap->GetSession(), inGroupID);

						args.GetReturnValue().Set(Boolean::New(isolate, Resultat));
	
					}

					else

					{

						//isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong argument arg[1] groupId string with Session object ")));

						args.GetReturnValue().SetNull();
					}

				}

			}

			else

			{
	
				isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong argument args[0] Session object or User object")));

				args.GetReturnValue().SetUndefined();
			}

		}
	
		else
		{

			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this> is not a Directory object")));

			args.GetReturnValue().SetUndefined();
		}

		
	}

	else
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of argument")));

		args.GetReturnValue().SetUndefined();
	}
}
void Directorywrap::LogOut(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	ControleDirectory* ContDirectory = new ControleDirectory();

	

	std::string Message;

	if (ControleDirectoryUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false) {


		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a Directory object")));
		args.GetReturnValue().SetUndefined();
	}
	else
	{
		Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

		

		if (ContDirectory->ControleGetPtDirectory(args, PtDirectoryWrap ->GetDirectory(),Message,1))
		{

			Utility util;

			Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args[0]->ToObject());

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


} 