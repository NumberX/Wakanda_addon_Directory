#include "Directorywrap.h"
#include"Sessionwrap.h"
#include"Directory.h"
#include"Session.h"
#include"Utility.h"
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

namespace WaDirectorywrap_data_v8 {
Persistent<Function> Directorywrap::constructor;

Directorywrap::Directorywrap() :ptdirectory() {

}

Directorywrap::~Directorywrap() {
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
  
	NODE_SET_PROTOTYPE_METHOD(tpl, "UserwrapBelongTo_1", UserwrapBelongTo_1);
  
	NODE_SET_PROTOTYPE_METHOD(tpl, "UserwrapBelongTo_2", UserwrapBelongTo_2);
  
	NODE_SET_PROTOTYPE_METHOD(tpl, "UserwrapBelongTo_3", UserwrapBelongTo_3);
 
	NODE_SET_PROTOTYPE_METHOD(tpl, "LogOut", LogOut);
  
	constructor.Reset(isolate, tpl->GetFunction());
  
	exports->Set(String::NewFromUtf8(isolate, "Directorywrap"),
               tpl->GetFunction());
}

void Directorywrap::New(const FunctionCallbackInfo<Value>& args) {
  
	
	
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
  
	  
	  if (args.Length() == 0) {
		
		  /*
		  Traitement du cas Directorywrap Dir=new Directorywrap(); 
		  */
		  Directorywrap* Obj_Directory_Wrap = new Directorywrap();
		
		  Directory *Pt_Directory = new Directory();
		
		  Obj_Directory_Wrap->ptdirectory = Pt_Directory;
		
		  Obj_Directory_Wrap->Wrap(args.This());
		
		  args.GetReturnValue().Set(args.This());
	}
	
	  
	  else if (args.Length() == 1) { 

		  /*
		  Traitement du cas Directorywrap Dir=new Directorywrap(Directory );
		  */
		
		  Directorywrap* Obj_Directory_Wrap = new Directorywrap();
		
		  Obj_Directory_Wrap->Wrap(args.This());
		
		  args.GetReturnValue().Set(args.This());
	}

  } else {
  }
}

void Directorywrap::LogIn(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

	Utility util;

	string user = util.V8Utf8ValueToStdString(args[0]);
	
	string password = util.V8Utf8ValueToStdString(args[1]);
	
	Session *PtSession = PtDirectoryWrap->ptdirectory->LogIn(user, password);
	
	Local<Object> ObjectSessionWrap = Sessionwrap::CreateSessionWrap(isolate, PtSession);

	args.GetReturnValue().Set(ObjectSessionWrap);
	
}
void Directorywrap::GetGroupwrapNames(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();

	Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());
	
	std::vector<std::string> Vector; 
	
	PtDirectoryWrap->ptdirectory->GetGroupNames(Vector);
	
	Utility util;
	
	Local<Array> Resulat = util.StdVectorToV8Array(isolate, Vector);

	args.GetReturnValue().Set(Resulat);
}
void Directorywrap::GetGroupwrap(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();
	
	Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());
	
	Utility util;

	string GroupId=util.V8Utf8ValueToStdString(args[0]);
	
	Group* PtGroup = PtDirectoryWrap->ptdirectory->GetGroup(GroupId);
	
	Local<Object> ObjectGroupWrap = Groupwrap::CreateGroupWrap(isolate, PtGroup);
	
	args.GetReturnValue().Set(ObjectGroupWrap);


}
void Directorywrap::GetUserwrap(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

	Utility util;

	string UserId = util.V8Utf8ValueToStdString(args[0]);

	User* PtUser = PtDirectoryWrap->ptdirectory->GetUser(UserId);

	Local<Object> ObjectUserWrap = Userwrap::CreateUserWrap(isolate, PtUser);

	args.GetReturnValue().Set(ObjectUserWrap);

}
void Directorywrap::GetSessionwrap(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

	Utility util;

	string SessionId = util.V8Utf8ValueToStdString(args[0]);

	Session* PtSession = PtDirectoryWrap->ptdirectory->GetSession(SessionId);

	Local<Object> ObjectUserWrap = Sessionwrap::CreateSessionWrap(isolate, PtSession);

	args.GetReturnValue().Set(ObjectUserWrap);
}
void Directorywrap::UserwrapBelongTo_1(const FunctionCallbackInfo<Value>& args) {
	
	Isolate* isolate = args.GetIsolate();

	Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());
	
	Utility util;
	
	string inGroupID = util.V8Utf8ValueToStdString(args[1]);
	
	Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args[0]->ToObject());
	
	bool resultat = PtDirectoryWrap->ptdirectory->UserBelongTo(PtSessionWrap->ptsession, inGroupID);
	 
	
	args.GetReturnValue().Set(Boolean::New(isolate, resultat));
}
void Directorywrap::UserwrapBelongTo_2(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

	Utility util;

	string inGroupID = util.V8Utf8ValueToStdString(args[1]);

	Userwrap* PtUserWrap = ObjectWrap::Unwrap<Userwrap>(args[0]->ToObject());

	bool resultat = PtDirectoryWrap->ptdirectory->UserBelongTo(PtUserWrap->ptuser, inGroupID);


	args.GetReturnValue().Set(Boolean::New(isolate, resultat));

}
void Directorywrap::UserwrapBelongTo_3(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

	Groupwrap* PtGroupWrap = ObjectWrap::Unwrap<Groupwrap>(args[1]->ToObject());

	Userwrap* PtUserWrap = ObjectWrap::Unwrap<Userwrap>(args[0]->ToObject());

	bool resultat = PtDirectoryWrap->ptdirectory->UserBelongTo(PtUserWrap->ptuser, PtGroupWrap->ptgroup);

	args.GetReturnValue().Set(Boolean::New(isolate, resultat));
}
void Directorywrap::LogOut(const FunctionCallbackInfo<Value>& args) {

	Isolate* isolate = args.GetIsolate();

	Directorywrap* PtDirectoryWrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());
	
	Utility util;

	string inSessionID = util.V8Utf8ValueToStdString(args[0]);
	
	bool resultat = PtDirectoryWrap->ptdirectory->LogOut(inSessionID);

	args.GetReturnValue().Set(Boolean::New(isolate, resultat));
}
} 