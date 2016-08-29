#include "UserwrapAsynchro.h"
#include"GroupwrapAsynchro.h"
#include"DirectorywrapAsynchro.h"
#include"ControleUser.h"
#include"Work.h"
#include"Thread_Data.h"
#include"Utility.h"
#include<string>

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
Local<Object> UserwrapAsynchro::CreateUserwrapAsynchro(Isolate* isolate, User* PtUser)
{

	EscapableHandleScope scope(isolate);

	Local<Value> argv[] = { Boolean::New(isolate, true) };
	
	Local<Context> context = isolate->GetCurrentContext();
	
	Local<Function> LocalFunction = Local<Function>::New(isolate, UserwrapAsynchro::constructor);
	
	Local<Object> ObjectUserWrapAsynchro = LocalFunction->NewInstance(context, 1, argv).ToLocalChecked();

	UserwrapAsynchro* PtUserWrapAsynchro = UserwrapAsynchro::Unwrap<UserwrapAsynchro>(ObjectUserWrapAsynchro);

	PtUserWrapAsynchro->ptuser = PtUser;

	return scope.Escape(ObjectUserWrapAsynchro);



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
	
	Isolate *isolate = Isolate::GetCurrent();
	
	if (ControleUserUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a Session object")));

		args.GetReturnValue().SetUndefined();
	}
	else{
		Work *work = new Work();

		work->request.data = work;

		UserwrapAsynchro* PtUserWrapAsynchro = ObjectWrap::Unwrap<UserwrapAsynchro>(args.Holder());
		string Message;

		ControleUser PtcontroleUser;
		if (PtcontroleUser.ControleGetPtUser(args,PtUserWrapAsynchro->ptuser, Message) == true)
		{
			Thread_Data Pt_UserWrapAsynchro_Intra;

			Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

			work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

			Local<Function> commeback = Local<Function>::Cast(args[0]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, GetDirectorywrapAsynchroWork, GetDirectorywrapAsynchroWorkComplete);

			args.GetReturnValue().Set(Undefined(isolate));
		}
		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetNull();
		}
	}

}

void UserwrapAsynchro::GetDirectorywrapAsynchroWork(uv_work_t  *request){
	Work *work = (Work*)(request->data);

	bool Resultat = "";

	Local<Object> ObjectDirectoryWrap = work->Intra_Data[0].Argument.PtUserwrapAsynchro->Pt_DirectorywrapAsynchro->handle();


	Thread_Data Resultat_data;

	Resultat_data.ObjectDirectoryWrap = ObjectDirectoryWrap;

	work->Intra_Data.push_back(Resultat_data);

}

void UserwrapAsynchro::GetDirectorywrapAsynchroWorkComplete(uv_work_t  *request, int status){

	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	Handle<Value> args[] = { Null(isolate), work->Intra_Data[0].ObjectDirectoryWrap };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;
}

void UserwrapAsynchro::GetNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
	Isolate* isolate = args.GetIsolate();

	if (ControleUserUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a User object")));

		args.GetReturnValue().SetNull();
	}
	else{
		Work *work = new Work();

		work->request.data = work;

		UserwrapAsynchro* PtUserWrapAsynchro = ObjectWrap::Unwrap<UserwrapAsynchro>(args.Holder());

		std::string resultat = "";

		std::string Message;

		ControleUser* PtControleUser = new ControleUser();

		if (PtControleUser->ControleGetPtUser(args, PtUserWrapAsynchro->ptuser, Message))
		{
			Thread_Data Pt_UserWrapAsynchro_Intra;

			Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

			work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

			Local<Function> commeback = Local<Function>::Cast(args[0]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, GetNameAsynchroWork, GetNameAsynchroWorkComplete);
		}
		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetNull();

		}
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

	char *Resultat_string = work->Intra_Data[0].Argument.Resultat_string;

	Local<String> Resultat_string_v = String::NewFromUtf8(isolate, Resultat_string);

	Handle<Value> args[] = { Null(isolate), Resultat_string_v };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}

void UserwrapAsynchro::BelongsToGroupwrapAsynchro(const FunctionCallbackInfo<Value>& args)
{

	Isolate* isolate = args.GetIsolate();

	bool resultat = false;

	ControleUser* PtControleUser = new ControleUser();
	std::string Message;

	if (ControleUserUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this is not a User object")));

		args.GetReturnValue().SetNull();
	}
	else{
		
		Work *work = new Work();

		work->request.data = work;

		UserwrapAsynchro* PtUserWrapAsynchro = ObjectWrap::Unwrap<UserwrapAsynchro>(args.Holder());

		Thread_Data Pt_UserWrapAsynchro_Intra;

		Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

		work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

		if (PtControleUser->ControleGetLenght(args, Message, 2))
		{
			if (GroupwrapAsynchro::ControleGroupUnwrap(args[0]->ToObject(), isolate)->BooleanValue() == true)
			{

				GroupwrapAsynchro* PtGroupWrapAsynchro = ObjectWrap::Unwrap<GroupwrapAsynchro>(args[0]->ToObject());

				Thread_Data Pt_GroupWrapAsynchro_Intra;

				Pt_GroupWrapAsynchro_Intra.Argument.PtGroupWrapAsynchro = PtGroupWrapAsynchro;

				work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

				Local<Function> commeback = Local<Function>::Cast(args[1]);

				work->callback.Reset(isolate, commeback);

				uv_queue_work(uv_default_loop(), &work->request, BelongsToGroupwrap_2AsynchroWork, BelongsToGroupwrap_2AsynchroWorkComplete);

			}
			else
			{
				if (PtControleUser->ControleGetType(args, Message, 0))
				{
					Utility util;

					string inGroupName = util.V8Utf8ValueToStdString(args[0]);


					Thread_Data Pt_inGroupID;

					Pt_inGroupID.Argument.GroupId = new char[inGroupName.length() + 1];;

					std::strcpy(Pt_inGroupID.Argument.GroupId, inGroupName.c_str());

					work->Input_Data.push_back(Pt_inGroupID);

					Local<Function> commeback = Local<Function>::Cast(args[1]);

					work->callback.Reset(isolate, commeback);

					uv_queue_work(uv_default_loop(), &work->request, BelongsToGroupwrap_1AsynchroWork, BelongsToGroupwrap_1AsynchroWorkComplete);



				}
				else
				{
					isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

					args.GetReturnValue().SetNull();
				}
			}


		}
		else
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

			args.GetReturnValue().SetUndefined();

		}
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

	work->Intra_Data.push_back(Resultat_Intra);

}

void UserwrapAsynchro::BelongsToGroupwrap_2AsynchroWorkComplete(uv_work_t  *request, int status){

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

void UserwrapAsynchro::IsLoggedInAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){

	Isolate* isolate = args.GetIsolate();

	bool resultat = false;

	if (ControleUserUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this> is not a User object")));

		args.GetReturnValue().SetUndefined();
	}
	else{
		Work *work = new Work();

		work->request.data = work;

		UserwrapAsynchro* PtUserWrapAsynchro = ObjectWrap::Unwrap<UserwrapAsynchro>(args.Holder());

		if (SessionwrapAsynchro::ControleSessionUnwrap(args[0]->ToObject(), isolate)->BooleanValue() == true)
		{

			Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args[0]->ToObject());
			if (PtSessionWrap->ptsession->IsValid())
			{
				Thread_Data Pt_UserWrapAsynchro_Intra;

				Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

				work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

				SessionwrapAsynchro* PtSessionWrapAsynchro = ObjectWrap::Unwrap<SessionwrapAsynchro>(args[0]->ToObject());

				Thread_Data Pt_SessionWrapAsynchro_Intra;

				Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

				work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

				Local<Function> commeback = Local<Function>::Cast(args[1]);

				work->callback.Reset(isolate, commeback);

				uv_queue_work(uv_default_loop(), &work->request, IsLoggedInAsynchroWork, IsLoggedInAsynchroWorkComplete);
			}
				

		}
		else
		{
			//isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong Session argument ")));

			args.GetReturnValue().Set(Boolean::New(isolate, resultat));
			//args.GetReturnValue().SetNull();
		}

		args.GetReturnValue().Set(Boolean::New(isolate, resultat));
	}



}

void UserwrapAsynchro::IsLoggedInAsynchroWork(uv_work_t  *request){
	Work *work = (Work*)(request->data);

	SessionwrapAsynchro* PtSessionWrapAsynchro = work->Intra_Data[1].Argument.ptSessionwrapAsynchro;

	UserwrapAsynchro* PtUserWrapAsynchro = work->Intra_Data[0].Argument.PtUserwrapAsynchro;

	Thread_Data Resultat_Intra;

	Resultat_Intra.Argument.Resultat = PtUserWrapAsynchro->ptuser->IsLoggedIn(PtSessionWrapAsynchro->ptsession);

	work->Intra_Data.push_back(Resultat_Intra);


}

void UserwrapAsynchro::IsLoggedInAsynchroWorkComplete(uv_work_t  *request, int status){

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


}
