#include"GroupwrapAsynchro.h"
#include<string>
#include<vector>
#include"Group.h"
#include"ControleGroup.h"
#include"Work.h"
#include"Thread_Data.h"
#include"UserwrapAsynchro.h"
#include<iostream>
using v8::Value;
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
using namespace Controle;
using namespace v8;
using namespace std;
using namespace WaDirectory;
namespace WaDirectorywrapAsynchro_data_v8 {

	Persistent<Function> GroupwrapAsynchro::constructor;

	Persistent<Value> GroupwrapAsynchro::prototype_Group_Synchrone;

	Local<Boolean> GroupwrapAsynchro::ControleGroupUnwrap(Local<Object> handle, Isolate* isolate)
	{
		EscapableHandleScope scope(isolate);

		if (!handle.IsEmpty() && handle->InternalFieldCount() == 1) {

			Local<Value> Pt_Prototype = handle->GetPrototype();
			Utility util;

			if (Pt_Prototype == prototype_Group_Synchrone) {
				Local<Boolean> Resultat = Boolean::New(isolate, true);
				return scope.Escape(Resultat);

			}


		}
		Local<Boolean> Resultat = Boolean::New(isolate, false);
		return scope.Escape(Resultat);
	}

	GroupwrapAsynchro::GroupwrapAsynchro() : ptgroup() {
	}

	GroupwrapAsynchro::~GroupwrapAsynchro() {
	}
	Local<Object> GroupwrapAsynchro::CreateGroupwrapAsynchro(Isolate* isolate, Group* PtGroup)
	{

		EscapableHandleScope scope(isolate);

		Local<Value> argv[] = { Boolean::New(isolate, true) };

		Local<Context> context = isolate->GetCurrentContext();

		Local<Function> LocalFunction = Local<Function>::New(isolate, GroupwrapAsynchro::constructor);

		Local<Object> ObjectGroupwrapAsynchro = LocalFunction->NewInstance(context, 1, argv).ToLocalChecked();

		GroupwrapAsynchro* PtGroupwrapAsynchro = GroupwrapAsynchro::Unwrap<GroupwrapAsynchro>(ObjectGroupwrapAsynchro);

		PtGroupwrapAsynchro->ptgroup = PtGroup;

		return scope.Escape(ObjectGroupwrapAsynchro);



	}
	void GroupwrapAsynchro::Init(Local<Object> exports) {

		Isolate* isolate = exports->GetIsolate();

		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);

		tpl->SetClassName(String::NewFromUtf8(isolate, "GroupwrapAsynchro"));

		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		NODE_SET_PROTOTYPE_METHOD(tpl, "GetNameAsynchro", GetNameAsynchro);

		NODE_SET_PROTOTYPE_METHOD(tpl, "GetUserwrapByNameAsynchro", GetUserwrapByNameAsynchro);

		NODE_SET_PROTOTYPE_METHOD(tpl, "GetSubGroupwrapNameAsynchro", GetSubGroupwrapNameAsynchro);

		NODE_SET_PROTOTYPE_METHOD(tpl, "GetDirectorywrapAsynchro", GetDirectorywrapAsynchro);

		constructor.Reset(isolate, tpl->GetFunction());

		exports->Set(String::NewFromUtf8(isolate, "GroupwrapAsynchro"),
			tpl->GetFunction());
	}

	void GroupwrapAsynchro::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		if (args.IsConstructCall()) {



			if (args.Length() == 1) {


				GroupwrapAsynchro* PtGroupWrap = new GroupwrapAsynchro();

				PtGroupWrap->Wrap(args.This());

				prototype_Group_Synchrone.Reset(isolate, args.This()->GetPrototype());

				args.GetReturnValue().Set(args.Holder());
			}
			else
			{

				isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "To create a object of Group you need to pass from Directory object ")));

				args.GetReturnValue().SetUndefined();

			}
		}
		else {

			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "To create a object of Group  you need to pass from Directory object ")));

			args.GetReturnValue().SetUndefined();
		}
	}
	
	void GroupwrapAsynchro::GetNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
		
		Isolate* isolate = args.GetIsolate();

		if (ControleGroupUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this> is not a Groupwrap object")));

			args.GetReturnValue().SetUndefined();
		}
		else{
			GroupwrapAsynchro* PtGroupWrapAsynchro = ObjectWrap::Unwrap<GroupwrapAsynchro>(args.Holder());

			std::string resultat = "";

			std::string Message;

			ControleGroup PtcontroleGroup;

			if (PtcontroleGroup.ControlePtGroup(PtGroupWrapAsynchro->ptgroup, Message) == true)
			{
				Work *work = new Work();

				work->request.data = work;

				Thread_Data Pt_GroupWrapAsynchro_Intra;

				Pt_GroupWrapAsynchro_Intra.Argument.PtGroupWrapAsynchro = PtGroupWrapAsynchro;

				work->Intra_Data.push_back(Pt_GroupWrapAsynchro_Intra);

				Local<Function> commeback = Local<Function>::Cast(args[0]);

				work->callback.Reset(isolate, commeback);

				uv_queue_work(uv_default_loop(), &work->request, GetNameAsynchroWork, GetNameAsynchroWorkComplete);

				args.GetReturnValue().Set(Undefined(isolate));
			}
			else
			{
				isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, Message.c_str())));

				args.GetReturnValue().SetNull();
			}

		}
	 }

	void GroupwrapAsynchro::GetNameAsynchroWork(uv_work_t  *request){

		Work *work = (Work*)(request->data);

		std::string Resultat = "";

		work->Intra_Data[0].Argument.PtGroupWrapAsynchro->ptgroup->GetName(Resultat);

		Thread_Data Resultat_string;

		Resultat_string.Argument.Resultat_string = new char[Resultat.length() + 1];;

		std::strcpy(Resultat_string.Argument.Resultat_string, Resultat.c_str());

		work->Intra_Data.push_back(Resultat_string);
	
	}

	void GroupwrapAsynchro::GetNameAsynchroWorkComplete(uv_work_t  *request, int status){
		
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

	void GroupwrapAsynchro::GetUserwrapByNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
		Isolate* isolate = args.GetIsolate();

		
		if (ControleGroupUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
		{
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "this> is not a Groupwrap object")));

			args.GetReturnValue().SetUndefined();
		}
		else{

			std::string res = "";

			Work *work = new Work();

			work->request.data = work;

			GroupwrapAsynchro* PtGroupWrapAsynchro = ObjectWrap::Unwrap<GroupwrapAsynchro>(args.Holder());


			std::string Message;

			ControleGroup *PtcontroleGroup = new ControleGroup();

			Thread_Data Pt_GroupWrapAsynchro_Intra;

			Pt_GroupWrapAsynchro_Intra.Argument.PtGroupWrapAsynchro = PtGroupWrapAsynchro;

			work->Intra_Data.push_back(Pt_GroupWrapAsynchro_Intra);

			Utility util;

			string user = util.V8Utf8ValueToStdString(args[0]);

			string password = util.V8Utf8ValueToStdString(args[1]);

			Thread_Data Pt_User;

			Thread_Data Pt_Password;

			Pt_User.Argument.user = new char[user.length() + 1];;

			std::strcpy(Pt_User.Argument.user, user.c_str());

			work->Input_Data.push_back(Pt_User);

			Pt_User.Argument.password = new char[password.length() + 1];;

			std::strcpy(Pt_User.Argument.password, password.c_str());

			work->Input_Data.push_back(Pt_Password);

			Local<Function> commeback = Local<Function>::Cast(args[2]);

			work->callback.Reset(isolate, commeback);

			uv_queue_work(uv_default_loop(), &work->request, GetUserwrapByNameAsynchroWork, GetUserwrapByNameAsynchroWorkComplete);

			args.GetReturnValue().Set(Undefined(isolate));

		}
	
	
	}

	void GroupwrapAsynchro::GetUserwrapByNameAsynchroWork(uv_work_t  *request){
	
		Work *work = (Work*)(request->data);

		string user = work->Input_Data[0].Argument.user;

		string password = work->Input_Data[0].Argument.password;

		Thread_Data Pt_UserWrapAsynchro_Intra;
		
		User *Pt_User = work->Intra_Data[0].Argument.PtGroupWrapAsynchro->ptgroup->GetUserByName(user, password);

		Pt_UserWrapAsynchro_Intra.Argument.Ptuser = Pt_User;
			
		work->Intra_Data.push_back(Pt_UserWrapAsynchro_Intra);
		
	
	
	}

	void GroupwrapAsynchro::GetUserwrapByNameAsynchroWorkComplete(uv_work_t  *request, int status){
		Isolate *isolate = Isolate::GetCurrent();

		HandleScope scoop(isolate);

		Work *work = (Work *)(request->data);

		char *Resultat_string = work->Intra_Data[0].Argument.Resultat_string;

		User *Pt_User = work->Intra_Data[0].Argument.Ptuser;

		Local<Object> ObjectUserwrapAsynchro = UserwrapAsynchro::CreateUserwrapAsynchro(isolate, Pt_User);

		Handle<Value> args[] = { Null(isolate), ObjectUserwrapAsynchro };

		Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

		work->callback.Reset();
	
	}

	void GroupwrapAsynchro::GetSubGroupwrapNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
	
		Isolate* isolate = args.GetIsolate();

		Work *work = new Work();

		work->request.data = work;

		GroupwrapAsynchro* PtGroupWrapAsynchro = ObjectWrap::Unwrap<GroupwrapAsynchro>(args.Holder());

		Thread_Data Pt_GroupWrapAsynchro_Intra;

		Pt_GroupWrapAsynchro_Intra.Argument.PtGroupWrapAsynchro = PtGroupWrapAsynchro;

		work->Intra_Data.push_back(Pt_GroupWrapAsynchro_Intra);
	
		Local<Function> commeback = Local<Function>::Cast(args[0]);

		work->callback.Reset(isolate, commeback);

		uv_queue_work(uv_default_loop(), &work->request, GetSubGroupwrapNameAsynchroWork, GetSubGroupwrapNameAsynchroWorkComplete);

		args.GetReturnValue().Set(Undefined(isolate));
		
	}
	

	void GroupwrapAsynchro::GetSubGroupwrapNameAsynchroWork(uv_work_t  *request){
		
		Work *work = (Work*)(request->data);

		std::vector<std::string> vector;

		work->Intra_Data[0].Argument.PtGroupWrapAsynchro->ptgroup->GetSubGroupName(vector);

		work->liste = vector;
		
	}

	void GroupwrapAsynchro::GetSubGroupwrapNameAsynchroWorkComplete(uv_work_t  *request, int status){
		Isolate *isolate = Isolate::GetCurrent();

		HandleScope scoop(isolate);

		Work *work = (Work *)(request->data);

		std::vector<std::string> Vector = work->liste;

		Utility util;

		Local<Array> array =util.StdVectorToV8Array(isolate,Vector) ;

		Handle<Value> args[] = { Null(isolate), array };

		Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 2, args);

		work->callback.Reset();
	
	}

    void GroupwrapAsynchro::GetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args){
	
	
	
	}
    void GroupwrapAsynchro::GetDirectorywrapAsynchroWork(uv_work_t  *request){
	
	
	}
    void GroupwrapAsynchro::GetDirectorywrapAsynchroWorkComplete(uv_work_t  *request, int status){
	
	
	}


} 