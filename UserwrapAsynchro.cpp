#include "UserwrapAsynchro.h"
#include"GroupwrapAsynchro.h"
#include"DirectorywrapAsynchro.h"
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

namespace WaDirectorywrapAsynchro_data_v8 {

Persistent<Function> UserwrapAsynchro::constructor;

UserwrapAsynchro::UserwrapAsynchro() : ptuser() {
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
  
  tpl->InstanceTemplate()->SetInternalFieldCount(2);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetDirectorywrapAsynchro", GetDirectorywrapAsynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetNameAsynchro", GetNameAsynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "BelongsToGroupwrap_1Asynchro", BelongsToGroupwrap_1Asynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "BelongsToGroupwrap_2Asynchro", BelongsToGroupwrap_2Asynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsLoggedInAsynchro", IsLoggedInAsynchro);
  
  constructor.Reset(isolate, tpl->GetFunction());
  
  exports->Set(String::NewFromUtf8(isolate, "UserwrapAsynchro"),
               tpl->GetFunction());
}

void UserwrapAsynchro::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
  
	  
	  if (args.Length() == 0) {

		  /*
		  Call from directory
		  */

		  UserwrapAsynchro* PtUserwrapAsynchro = new UserwrapAsynchro();

		  User *Ptuser = new User();

		  PtUserwrapAsynchro->ptuser = Ptuser;

		  PtUserwrapAsynchro->Wrap(args.Holder());

		  args.GetReturnValue().Set(args.Holder());
	  }
	  else if (args.Length() == 1) { 

		  /*
		  Traitement du cas UserwrapAsynchro User=new UserwrapAsynchro();
		  */

		  UserwrapAsynchro* PtUserwrapAsynchro = new UserwrapAsynchro();

		  PtUserwrapAsynchro->Wrap(args.Holder());

		  args.GetReturnValue().Set(args.Holder());
	  }
  } else {

  }
}

void UserwrapAsynchro::GetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){


}

void UserwrapAsynchro::GetDirectorywrapAsynchroWork(const v8::FunctionCallbackInfo<v8::Value>& args){


}

void UserwrapAsynchro::GetDirectorywrapAsynchroWorkComplete(const v8::FunctionCallbackInfo<v8::Value>& args){


}

void UserwrapAsynchro::GetNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
	Isolate* isolate = args.GetIsolate();

	Work *work = new Work();

	work->request.data = work;

	UserwrapAsynchro* PtUserWrapAsynchro = ObjectWrap::Unwrap<UserwrapAsynchro>(args.Holder());

	Thread_Data Pt_UserWrapAsynchro_Intra;

	Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

	work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

	Local<Function> commeback = Local<Function>::Cast(args[0]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, GetNameAsynchroWork, GetNameAsynchroWorkComplete);


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


}

void UserwrapAsynchro::BelongsToGroupwrap_1Asynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
	Isolate* isolate = args.GetIsolate();

	Work *work = new Work();

	work->request.data = work;

	UserwrapAsynchro* PtUserWrapAsynchro = ObjectWrap::Unwrap<UserwrapAsynchro>(args.Holder());

	Thread_Data Pt_UserWrapAsynchro_Intra;

	Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

	work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

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

}

void UserwrapAsynchro::BelongsToGroupwrap_2Asynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
	
	Isolate* isolate = args.GetIsolate();

	Work *work = new Work();

	work->request.data = work;

	UserwrapAsynchro* PtUserWrapAsynchro = ObjectWrap::Unwrap<UserwrapAsynchro>(args.Holder());

	Thread_Data Pt_UserWrapAsynchro_Intra;

	Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

	work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

	GroupwrapAsynchro* PtGroupWrapAsynchro = ObjectWrap::Unwrap<GroupwrapAsynchro>(args[0]->ToObject());

	Thread_Data Pt_GroupWrapAsynchro_Intra;

	Pt_GroupWrapAsynchro_Intra.Argument.PtGroupWrapAsynchro = PtGroupWrapAsynchro;

	work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

	Local<Function> commeback = Local<Function>::Cast(args[1]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, BelongsToGroupwrap_2AsynchroWork, BelongsToGroupwrap_2AsynchroWorkComplete);



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
}

void UserwrapAsynchro::IsLoggedInAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){

	Isolate* isolate = args.GetIsolate();

	Work *work = new Work();

	work->request.data = work;

	UserwrapAsynchro* PtUserWrapAsynchro = ObjectWrap::Unwrap<UserwrapAsynchro>(args.Holder());

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

}


}
