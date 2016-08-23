#include "SessionwrapAsynchro.h"
#include "UserwrapAsynchro.h"
#include"Thread_Data.h"
#include"Work.h"
#include<string>
#include<iostream>
#include"Session.h"
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
using v8::Handle;
using v8::HandleScope;
using namespace v8;
using namespace WaDirectory;
using namespace std;

namespace WaDirectorywrapAsynchro_data_v8 {

Persistent<Function> SessionwrapAsynchro::constructor;

SessionwrapAsynchro::SessionwrapAsynchro():ptsession()  {
	
}

SessionwrapAsynchro::~SessionwrapAsynchro() {

}
Local<Object> SessionwrapAsynchro::CreateSessionwrapAsynchro(Isolate* isolate, Session* PtSession)
{
	EscapableHandleScope scope(isolate);

	Local<Value> argv[] = { Boolean::New(isolate, true) };
	
	Local<Context> context = isolate->GetCurrentContext();
	
	Local<Function> LocalFunct = Local<Function>::New(isolate, SessionwrapAsynchro::constructor);
	
	Local<Object> ObjectSessionwrapAsynchro = LocalFunct->NewInstance(context, 1, argv).ToLocalChecked();
	
	SessionwrapAsynchro* PtSessionwrapAsynchro = SessionwrapAsynchro::Unwrap<SessionwrapAsynchro>(ObjectSessionwrapAsynchro);

	PtSessionwrapAsynchro->ptsession = PtSession;

	return scope.Escape(ObjectSessionwrapAsynchro);



}
void SessionwrapAsynchro::Init(Local<Object> exports) {

  Isolate* isolate = exports->GetIsolate();
  
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  
  tpl->SetClassName(String::NewFromUtf8(isolate, "SessionwrapAsynchro"));
  
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetUserwrapAsynchro", GetUserwrapAsynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetWASID", GetWASIDAsynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetDirectorywrapAsynchro", GetDirectorywrapAsynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsValid", IsValidAsynchro);
  
  NODE_SET_PROTOTYPE_METHOD(tpl, "LogOut", LogOutAsynchro);

  constructor.Reset(isolate, tpl->GetFunction());
  
  exports->Set(String::NewFromUtf8(isolate, "SessionwrapAsynchro"),
               tpl->GetFunction());
}

void SessionwrapAsynchro::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
	
	  if (args.Length() == 0) {
		  /*Traitement du cas UserwrapAsynchro PtUserWarp = new UserwrapAsynchro() */
		  SessionwrapAsynchro*  PtSessionwrapAsynchro= new SessionwrapAsynchro();
		  
		  Session *PtSession = new Session();
		  
		  PtSessionwrapAsynchro->ptsession = PtSession;
		  
		  PtSessionwrapAsynchro->Wrap(args.Holder());
		  
		  args.GetReturnValue().Set(args.Holder());
	  }
	  
	  else if (args.Length() == 1) { 
		  /*Traitement du cas UserwrapAsynchro PtUserWarp = new UserwrapAsynchro(User) */
		
		  SessionwrapAsynchro* PtSessionwrapAsynchro = new SessionwrapAsynchro();
		  
		  PtSessionwrapAsynchro->Wrap(args.This());
		  
		  args.GetReturnValue().Set(args.Holder());
	  }
  } else {
    
  }
}
void SessionwrapAsynchro::GetUserwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
	
	
	Isolate* isolate = args.GetIsolate();
	
	Work *work = new Work();

	work->request.data = work;

	SessionwrapAsynchro* PtSessionWrapAsynchro = ObjectWrap::Unwrap<SessionwrapAsynchro>(args.Holder());

	Thread_Data Pt_SessionWrapAsynchro_Intra;

	Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

	work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);

	Local<Function> commeback = Local<Function>::Cast(args[0]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, GetUserwrapAsynchroWork, GetUserwrapAsynchroWorkComplete);

	args.GetReturnValue().Set(Undefined(isolate));

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

	User *PtUser = work->Intra_Data[0].Argument.Ptuser;

	Local<Object> ObjectUserwrapAsynchro = UserwrapAsynchro::CreateUserwrapAsynchro(isolate, PtUser);

	Handle<Value> args[] = { Null(isolate), ObjectUserwrapAsynchro };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}
void SessionwrapAsynchro::GetWASIDAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){


	Isolate* isolate = args.GetIsolate();

	Work *work = new Work();

	work->request.data = work;

	SessionwrapAsynchro* PtSessionWrapAsynchro = ObjectWrap::Unwrap<SessionwrapAsynchro>(args.Holder());

	Thread_Data Pt_SessionWrapAsynchro_Intra;

	Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

	work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);

	Local<Function> commeback = Local<Function>::Cast(args[0]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, GetWASIDAsynchroWork, GetWASIDAsynchroWorkComplete);

	args.GetReturnValue().Set(Undefined(isolate));




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

	char *Resultat_string = work->Intra_Data[0].Argument.Resultat_string;

	Local<String> Resultat_string_v = String::NewFromUtf8(isolate, Resultat_string);

	Handle<Value> args[] = { Null(isolate), Resultat_string_v };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;


};
void SessionwrapAsynchro::GetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){};
void SessionwrapAsynchro::GetDirectorywrapAsynchroWork(uv_work_t  *request){};
void SessionwrapAsynchro::GetDirectorywrapAsynchroWorkComplete(uv_work_t  *request, int status){};
void SessionwrapAsynchro::IsValidAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){

	Isolate* isolate = args.GetIsolate();

	Work *work = new Work();

	work->request.data = work;

	SessionwrapAsynchro* PtSessionWrapAsynchro = ObjectWrap::Unwrap<SessionwrapAsynchro>(args.Holder());

	Thread_Data Pt_SessionWrapAsynchro_Intra;

	Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

	work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);

	Local<Function> commeback = Local<Function>::Cast(args[0]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, IsValidAsynchroWork, IsValidAsynchroWorkComplete);

	args.GetReturnValue().Set(Undefined(isolate));

};
void SessionwrapAsynchro::IsValidAsynchroWork(uv_work_t  *request){
	Work *work = (Work*)(request->data);

	bool Resultat = "";

	Resultat=work->Intra_Data[0].Argument.ptSessionwrapAsynchro->ptsession->IsValid();

	Thread_Data Resultat_data;

	Resultat_data.Argument.Resultat = Resultat;

	work->Intra_Data.push_back(Resultat_data);
};
void SessionwrapAsynchro::IsValidAsynchroWorkComplete(uv_work_t  *request, int status){
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	bool Resultat = work->Intra_Data[0].Argument.Resultat;

	Local<Boolean> Resultat_v8= Boolean::New(isolate, Resultat);

	Handle<Value> args[] = { Null(isolate), Resultat_v8 };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

};
void SessionwrapAsynchro::LogOutAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
	Isolate* isolate = args.GetIsolate();

	Work *work = new Work();

	work->request.data = work;

	SessionwrapAsynchro* PtSessionWrapAsynchro = ObjectWrap::Unwrap<SessionwrapAsynchro>(args.Holder());

	Thread_Data Pt_SessionWrapAsynchro_Intra;

	Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

	work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);

	Local<Function> commeback = Local<Function>::Cast(args[0]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, LogOutAsynchroWork, LogOutAsynchroWorkComplete);

	args.GetReturnValue().Set(Undefined(isolate));

};
void SessionwrapAsynchro::LogOutAsynchroWork(uv_work_t  *request){
	
	Work *work = (Work*)(request->data);

	work->Intra_Data[0].Argument.ptSessionwrapAsynchro->ptsession->LogOut();

};
void SessionwrapAsynchro::LogOutAsynchroWorkComplete(uv_work_t  *request, int status){

	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	Handle<Value> args[] = { Null(isolate)};

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 1, args);

	work->callback.Reset();

	delete work;


};

}

