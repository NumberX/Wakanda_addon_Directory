#include "DirectorywrapAsynchro.h"
#include"SessionwrapAsynchro.h"
#include"Directory.h"
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
  

  
	constructor.Reset(isolate, tpl->GetFunction());
  
	exports->Set(String::NewFromUtf8(isolate, "DirectorywrapAsynchro"),
               tpl->GetFunction());
}

void DirectorywrapAsynchro::New(const FunctionCallbackInfo<Value>& args) {
  
	
	
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
  
	  
	  if (args.Length() == 0) {
		
		  /*
		  Traitement du cas DirectorywrapAsynchro Dir=new DirectorywrapAsynchro(); 
		  */
		  DirectorywrapAsynchro* Obj_Directory_wrapAsynchro = new DirectorywrapAsynchro();
		
		  Directory *Pt_Directory = new Directory();
		
		  Obj_Directory_wrapAsynchro->ptdirectory = Pt_Directory;
		
		  Obj_Directory_wrapAsynchro->Wrap(args.This());
		
		  args.GetReturnValue().Set(args.This());
	}
	
	  
	  else if (args.Length() == 1) { 

		  /*
		  Traitement du cas DirectorywrapAsynchro Dir=new DirectorywrapAsynchro(Directory );
		  */
		
		  DirectorywrapAsynchro* Obj_Directory_wrapAsynchro = new DirectorywrapAsynchro();
		
		  Obj_Directory_wrapAsynchro->Wrap(args.This());
		
		  args.GetReturnValue().Set(args.This());
	}

  } else {
  }
}



void DirectorywrapAsynchro::LogInAsynchro(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	Work *work = new Work();

	work->request.data = work;

	DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

	Thread_Data Pt_DirectoryWrapAsynchro_Intra;

	Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

	work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

	Utility util;

	string user = util.V8Utf8ValueToStdString(args[0]);

	Thread_Data Pt_User;

	Pt_User.Argument.user = new char[user.length() + 1];;

	std::strcpy(Pt_User.Argument.user, user.c_str());

	work->Input_Data.push_back(Pt_User);

	string password = util.V8Utf8ValueToStdString(args[1]);

	Thread_Data Pt_Password;

	Pt_Password.Argument.password = new char[password.length() + 1];

	std::strcpy(Pt_Password.Argument.password, password.c_str());

	work->Input_Data.push_back(Pt_Password);

	Local<Function> commeback = Local<Function>::Cast(args[2]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, LogInAsynchroWork, LogInAsynchroWorkComplete);

	args.GetReturnValue().Set(Undefined(isolate));

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

	ISession *PtSession = work->Intra_Data[0].Argument.PtSession;

	Local<Object> ObjectSessionwrapAsynchro = SessionwrapAsynchro::CreateSessionwrapAsynchro(isolate, PtSession);

	Handle<Value> args[] = { Null(isolate), ObjectSessionwrapAsynchro };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;
}
void DirectorywrapAsynchro::GetGroupwrapNamesAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args)
{

	Isolate* isolate = args.GetIsolate();

	Work *work = new Work();

	work->request.data = work;

	DirectorywrapAsynchro* PtDirectoryWrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

	Thread_Data Pt_DirectoryWrapAsynchro_Intra;

	Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectoryWrapAsynchro;

	Local<Function> commeback = Local<Function>::Cast(args[0]);

	work->callback.Reset(isolate, commeback);

	work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

	uv_queue_work(uv_default_loop(), &work->request, GetGroupwrapNamesAsynchroWork, GetGroupwrapNamesAsynchroWorkComplete);

	args.GetReturnValue().Set(Undefined(isolate));


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

	DirectorywrapAsynchro* PtDirectoryWrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

	Utility util;

	Work *work = new Work();

	work->request.data = work;

	DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

	Thread_Data Pt_DirectoryWrapAsynchro_Intra;

	Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

	work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

	string GroupId = util.V8Utf8ValueToStdString(args[0]);

	Thread_Data Pt_GroupId;

	Pt_GroupId.Argument.GroupId = new char[GroupId.length() + 1];;

	std::strcpy(Pt_GroupId.Argument.GroupId, GroupId.c_str());

	work->Input_Data.push_back(Pt_GroupId);

	Local<Function> commeback = Local<Function>::Cast(args[1]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, GetGroupwrapAsynchroWork, GetGroupwrapAsynchroWorkComplete);

	args.GetReturnValue().Set(Undefined(isolate));

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

	IGroup *PtGroup = work->Intra_Data[0].Argument.PtGroup;

	Local<Object> ObjectGroupwrapAsynchro = GroupwrapAsynchro::CreateGroupwrapAsynchro(isolate, PtGroup);

	Handle<Value> args[] = { Null(isolate), ObjectGroupwrapAsynchro };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;


}
void DirectorywrapAsynchro::GetUserwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();

	Utility util;

	Work *work = new Work();

	work->request.data = work;

	DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

	Thread_Data Pt_DirectoryWrapAsynchro_Intra;

	Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

	work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

	string UserId = util.V8Utf8ValueToStdString(args[0]);

	Thread_Data Pt_UserId;

	Pt_UserId.Argument.user = new char[UserId.length() + 1];;

	std::strcpy(Pt_UserId.Argument.user, UserId.c_str());

	work->Input_Data.push_back(Pt_UserId);

	Local<Function> commeback = Local<Function>::Cast(args[1]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, GetUserwrapAsynchroWork, GetUserwrapAsynchroWorkComplete);

	args.GetReturnValue().Set(Undefined(isolate));


}
void DirectorywrapAsynchro::GetUserwrapAsynchroWork(uv_work_t  *request){

	Work *work = (Work*)(request->data);

	string UserId = work->Input_Data[0].Argument.user;


	Thread_Data Pt_UserWrapAsynchro_Intra;

	Pt_UserWrapAsynchro_Intra.Argument.Ptuser = work->Intra_Data[0].Argument.PtDirectorywrapAsynchro->ptdirectory->GetUser(UserId, "");

	work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

}
void DirectorywrapAsynchro::GetUserwrapAsynchroWorkComplete(uv_work_t  *request, int status){
	
	Isolate *isolate = Isolate::GetCurrent();

	HandleScope scoop(isolate);

	Work *work = (Work *)(request->data);

	IUser *PtUser = work->Intra_Data[0].Argument.Ptuser;

	Local<Object> ObjectUserwrapAsynchro = UserwrapAsynchro::CreateUserwrapAsynchro(isolate, PtUser);

	Handle<Value> args[] = { Null(isolate), ObjectUserwrapAsynchro };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}
void DirectorywrapAsynchro::GetSessionwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){

	Isolate* isolate = args.GetIsolate();

	Utility util;

	Work *work = new Work();

	work->request.data = work;

	DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

	Thread_Data Pt_DirectoryWrapAsynchro_Intra;

	Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

	work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

	string SessionId = util.V8Utf8ValueToStdString(args[0]);

	Thread_Data Pt_SessionId;

	Pt_SessionId.Argument.SessionId = new char[SessionId.length() + 1];;

	std::strcpy(Pt_SessionId.Argument.SessionId, SessionId.c_str());

	work->Input_Data.push_back(Pt_SessionId);

	Local<Function> commeback = Local<Function>::Cast(args[1]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, GetSessionwrapAsynchroWork, GetSessionwrapAsynchroWorkComplete);

	args.GetReturnValue().Set(Undefined(isolate));

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

	ISession *PtSession = work->Intra_Data[0].Argument.PtSession;

	Local<Object> ObjectSessionwrapAsynchro = SessionwrapAsynchro::CreateSessionwrapAsynchro(isolate, PtSession);

	Handle<Value> args[] = { Null(isolate), ObjectSessionwrapAsynchro };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}
void DirectorywrapAsynchro::UserwrapBelongAsynchroTo_1(const v8::FunctionCallbackInfo<v8::Value>& args){
	
	Isolate* isolate = args.GetIsolate();

	Utility util;

	Work *work = new Work();

	work->request.data = work;

	DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

	Thread_Data Pt_DirectoryWrapAsynchro_Intra;

	Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

	work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

	SessionwrapAsynchro* PtSessionWrapAsynchro = ObjectWrap::Unwrap<SessionwrapAsynchro>(args[0]->ToObject());

	Thread_Data Pt_SessionWrapAsynchro_Intra;

	Pt_SessionWrapAsynchro_Intra.Argument.ptSessionwrapAsynchro = PtSessionWrapAsynchro;

	work->Intra_Data.push_back(Pt_SessionWrapAsynchro_Intra);


	string inGroupID = util.V8Utf8ValueToStdString(args[1]);

	Thread_Data Pt_inGroupID;

	Pt_inGroupID.Argument.GroupId = new char[inGroupID.length() + 1];;

	std::strcpy(Pt_inGroupID.Argument.GroupId, inGroupID.c_str());

	work->Input_Data.push_back(Pt_inGroupID);

	Local<Function> commeback = Local<Function>::Cast(args[2]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, UserwrapBelongAsynchroWorkTo_1, UserwrapBelongAsynchroWorkCompleteTo_1);

	args.GetReturnValue().Set(Undefined(isolate));

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

	bool Resultat = work->Intra_Data[0].Argument.Resultat;

	Local<Boolean> Resultat_v8 = Boolean::New(isolate, Resultat);

	Handle<Value> args[] = { Null(isolate), Resultat_v8 };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}
void DirectorywrapAsynchro::UserwrapBelongAsynchroTo_2(const v8::FunctionCallbackInfo<v8::Value>& args){

	Isolate* isolate = args.GetIsolate();

	Utility util;

	Work *work = new Work();

	work->request.data = work;

	DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

	Thread_Data Pt_DirectoryWrapAsynchro_Intra;

	Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

	work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

	UserwrapAsynchro* PtUserWrapAsynchro = ObjectWrap::Unwrap<UserwrapAsynchro>(args[0]->ToObject());

	Thread_Data Pt_UserWrapAsynchro_Intra;

	Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

	work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);


	string inGroupID = util.V8Utf8ValueToStdString(args[1]);

	Thread_Data Pt_inGroupID;

	Pt_inGroupID.Argument.GroupId = new char[inGroupID.length() + 1];;

	std::strcpy(Pt_inGroupID.Argument.GroupId, inGroupID.c_str());

	work->Input_Data.push_back(Pt_inGroupID);

	Local<Function> commeback = Local<Function>::Cast(args[2]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, UserwrapBelongAsynchroWorkTo_2, UserwrapBelongAsynchroWorkCompleteTo_2);

	args.GetReturnValue().Set(Undefined(isolate));

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

	bool Resultat = work->Intra_Data[0].Argument.Resultat;

	Local<Boolean> Resultat_v8 = Boolean::New(isolate, Resultat);

	Handle<Value> args[] = { Null(isolate), Resultat_v8 };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}
void DirectorywrapAsynchro::UserwrapBelongAsynchroTo_3(const v8::FunctionCallbackInfo<v8::Value>& args){

	Isolate* isolate = args.GetIsolate();

	Utility util;

	Work *work = new Work();

	work->request.data = work;

	DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

	Thread_Data Pt_DirectoryWrapAsynchro_Intra;

	Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

	work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

	UserwrapAsynchro* PtUserWrapAsynchro = ObjectWrap::Unwrap<UserwrapAsynchro>(args[0]->ToObject());

	Thread_Data Pt_UserWrapAsynchro_Intra;

	Pt_UserWrapAsynchro_Intra.Argument.PtUserwrapAsynchro = PtUserWrapAsynchro;

	work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);

	GroupwrapAsynchro* PtGroupWrapAsynchro = ObjectWrap::Unwrap<GroupwrapAsynchro>(args[1]->ToObject());

	Thread_Data Pt_GroupWrapAsynchro_Intra;

	Pt_GroupWrapAsynchro_Intra.Argument.PtGroupWrapAsynchro = PtGroupWrapAsynchro;

	work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);


	Local<Function> commeback = Local<Function>::Cast(args[2]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, UserwrapBelongAsynchroWorkTo_3, UserwrapBelongAsynchroWorkCompleteTo_3);

	args.GetReturnValue().Set(Undefined(isolate));

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

	bool Resultat = work->Intra_Data[0].Argument.Resultat;

	Local<Boolean> Resultat_v8 = Boolean::New(isolate, Resultat);

	Handle<Value> args[] = { Null(isolate), Resultat_v8 };

	Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

	work->callback.Reset();

	delete work;

}
void DirectorywrapAsynchro::LogOutAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args)
{

	Isolate* isolate = args.GetIsolate();

	Utility util;

	Work *work = new Work();

	work->request.data = work;

	DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

	Thread_Data Pt_DirectoryWrapAsynchro_Intra;

	Pt_DirectoryWrapAsynchro_Intra.Argument.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

	work->Intra_Data.push_back(Pt_DirectoryWrapAsynchro_Intra);

	string SessionID = util.V8Utf8ValueToStdString(args[0]);

	Thread_Data Pt_SessionID;

	Pt_SessionID.Argument.SessionId = new char[SessionID.length() + 1];;

	std::strcpy(Pt_SessionID.Argument.SessionId, SessionID.c_str());

	work->Input_Data.push_back(Pt_SessionID);

	Local<Function> commeback = Local<Function>::Cast(args[1]);

	work->callback.Reset(isolate, commeback);

	uv_queue_work(uv_default_loop(), &work->request, LogOutAsynchroWork, LogOutAsynchroWorkComplete);

	args.GetReturnValue().Set(Undefined(isolate));

}
void DirectorywrapAsynchro::LogOutAsynchroWork(uv_work_t  *request)
{


}
void DirectorywrapAsynchro::LogOutAsynchroWorkComplete(uv_work_t  *request, int status)
{


}

} 