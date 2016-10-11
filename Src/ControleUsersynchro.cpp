#include "ControleUsersynchro.h"
#include"Utility.h"
#include<iostream>
using namespace std;

namespace WaDirectory_Controle{
	ControleUsersynchro::ControleUsersynchro()
	{
	}


	ControleUsersynchro::~ControleUsersynchro()
	{
	}
	bool ControleUsersynchro::ControleValideUserData(IUser *PtUser, string& Message)
	{
		if (PtUser == NULL)
		{
			Message = "PtUser is Null";
			return false;
		}
		return true;

	}

	vector<DataControlesyn>*              ControleUsersynchro::ControleGetNamesynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		vector<DataControlesyn>* Output = NULL;

		if (ControleGetLenght(args, Message, 0)){
			if (ControleUserUnwrap(args, Message, 10) == true)
			{

				Userwrap* PtUserwrap = ObjectWrap::Unwrap<Userwrap>(args.Holder());

				if (ControleValideUserData(PtUserwrap->GetUserData(), Message))
				{ 
					Output = new vector<DataControlesyn>();

					DataControlesyn dataptUser;

					dataptUser.Output.PtUserwrap = PtUserwrap;

					Output->push_back(dataptUser);

					Controle = true;

					return Output;
				}
				}
			
		}
		return Output;
	}
	vector<DataControlesyn>*              ControleUsersynchro::ControleBelongsToGroupwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message,int &Methode)
{

	Isolate* isolate = args.GetIsolate();

	vector<DataControlesyn>* Output = NULL;

	if (ControleGetLenght(args, Message, 2)){
		if (ControleUserUnwrap(args, Message, 10) == true)
		{


			Userwrap* PtUserwrap = ObjectWrap::Unwrap<Userwrap>(args.Holder());
			if (ControleValideUserData(PtUserwrap->GetUserData(), Message))
			{
				Output = new vector<DataControlesyn>();

				DataControlesyn dataptUser;

				dataptUser.Output.PtUserwrap = PtUserwrap;

				Output->push_back(dataptUser);

				if (ControleGroupUnwrap(args, Message, 0) == true){

					Groupwrap* Ptgroupwrap = ObjectWrap::Unwrap<Groupwrap>(args[0]->ToObject());

					DataControlesyn Ptgroupdata;

					Ptgroupdata.Output.PtGroupwrap = Ptgroupwrap;

					Output->push_back(Ptgroupdata);

					Methode = 1;

					Controle = true;

					return Output;
				}
				if (Controlestring(args, Message, 0) == true){

					Tools::Utility util;

					string GroupId = util.V8Utf8ValueToStdString(args[0]);

					DataControlesyn dataGroupId;

					dataGroupId.Output.GroupId = new char[GroupId.length() + 1];;

					std::strcpy(dataGroupId.Output.GroupId, GroupId.c_str());

					Output->push_back(dataGroupId);

					Methode = 2;

					Controle = true;

					return Output;

				}
			}
		}
	}
	return Output;

	
}
vector<DataControlesyn>* 			 ControleUsersynchro::ControleGetDirectorywrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
{
	Isolate* isolate = args.GetIsolate();

	vector<DataControlesyn>* Output = NULL;

	if (ControleGetLenght(args, Message, 0)){
		if (ControleUserUnwrap(args, Message, 10) == true)
		{

			Userwrap* PtUserwrap = ObjectWrap::Unwrap<Userwrap>(args.Holder());
			
			if (ControleValideUserData(PtUserwrap->GetUserData(), Message))
			{
				Output = new vector<DataControlesyn>();


				DataControlesyn dataptUser;

				dataptUser.Output.PtUserwrap = PtUserwrap;

				Output->push_back(dataptUser);

				Controle = true;

				return Output;
			}
		}
	}
	return Output;
}
vector<DataControlesyn>*              ControleUsersynchro::ControleIsLoggedInsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message,int& Methode1)
{
	Isolate* isolate = args.GetIsolate();

	vector<DataControlesyn>* Output = NULL;

	if (ControleUserUnwrap(args, Message, 10) == true)
	{
		Userwrap* PtUserwrap = ObjectWrap::Unwrap<Userwrap>(args.Holder());

		DataControlesyn dataptUser;

		dataptUser.Output.PtUserwrap = PtUserwrap;

		if (ControleValideUserData(PtUserwrap->GetUserData(), Message))
		{

	
			if (ControleGetLenght(args, Message, 2)){

		
			if (ControleSessionUnwrap(args, Message, 0) == true){
			
				Output = new vector<DataControlesyn>();
				
				Output->push_back(dataptUser);

				Sessionwrap* PtSessionwrap = ObjectWrap::Unwrap<Sessionwrap>(args[0]->ToObject());

				DataControlesyn dataptSession;

				dataptSession.Output.PtSessionwrap = PtSessionwrap;

				Output->push_back(dataptSession);

				Controle = true;

				Methode1 = 1;

				return Output;
			}
			}
			if (ControleGetLenght(args, Message, 1)){

					Output = new vector<DataControlesyn>();

					Output->push_back(dataptUser);

					Local<Context> CurentContext = isolate->GetCurrentContext();

					DataControlesyn dataPtSession;

					Local<Value> SessionObject1 = CurentContext->GetEmbedderData(0);

					Local<Object> SessionObject = SessionObject1->ToObject();

					Sessionwrap* PtSession = Sessionwrap::Unwrap<Sessionwrap>(SessionObject);

					dataPtSession.Output.PtSessionwrap = PtSession;

					Output->push_back(dataPtSession);

					Methode1 = 2;

					Controle = true;

					return Output;
					
			}
		}
	}
	return Output;
}


}