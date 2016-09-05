#include "ControleUserAsynchro.h"

namespace WaDirectorywrapAsynchro_data_v8{
	ControleUserAsynchro::ControleUserAsynchro()
	{
	}


	ControleUserAsynchro::~ControleUserAsynchro()
	{
	}

	vector<DataControle>*              ControleUserAsynchro::ControleGetNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		vector<DataControle>* Output = NULL;

		if (ControleGetLenght(args, Message, 1)){
			if (ControleUserUnwrap(args, Message, 10) == true)
			{

				Output = new vector<DataControle>();

				UserwrapAsynchro* PtUserwrap = ObjectWrap::Unwrap<UserwrapAsynchro>(args.Holder());

				DataControle dataptUser;

				dataptUser.Output.PtUserwrapAsynchro = PtUserwrap;

				Output->push_back(dataptUser);

				Controle = true;

				return Output;
			}
		}
		return Output;
	}
	vector<DataControle>*              ControleUserAsynchro::ControleBelongsToGroupwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message,int &Methode)
{

	Isolate* isolate = args.GetIsolate();

	vector<DataControle>* Output = NULL;

	if (ControleGetLenght(args, Message, 2)){
		if (ControleUserUnwrap(args, Message, 10) == true)
		{
			Output = new vector<DataControle>();

			UserwrapAsynchro* PtUserwrap = ObjectWrap::Unwrap<UserwrapAsynchro>(args.Holder());

			DataControle dataptUser;

			dataptUser.Output.PtUserwrapAsynchro = PtUserwrap;

			Output->push_back(dataptUser);

			if (ControleGroupUnwrap(args, Message, 0) == true){

				GroupwrapAsynchro* Ptgroupwrap = ObjectWrap::Unwrap<GroupwrapAsynchro>(args[0]->ToObject());

				DataControle Ptgroupdata;

				Ptgroupdata.Output.PtGroupwrapAsynchro = Ptgroupwrap;

				Output->push_back(Ptgroupdata);

				Methode = 1;

				Controle = true;

				return Output;
			}
			if (Controlestring(args, Message, 0) == true){

				Utility util;

				string GroupId = util.V8Utf8ValueToStdString(args[0]);

				DataControle dataGroupId;

				dataGroupId.Output.GroupId = new char[GroupId.length() + 1];;

				std::strcpy(dataGroupId.Output.GroupId, GroupId.c_str());

				Output->push_back(dataGroupId);

				Methode = 2;

				Controle = true;

				return Output;
			}
		}
	}
	return Output;

	
}
vector<DataControle>* 			 ControleUserAsynchro::ControleGetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
{
	Isolate* isolate = args.GetIsolate();

	vector<DataControle>* Output = NULL;

	if (ControleGetLenght(args, Message, 1)){
		if (ControleUserUnwrap(args, Message, 10) == true)
		{

			Output = new vector<DataControle>();

			UserwrapAsynchro* PtUserwrap = ObjectWrap::Unwrap<UserwrapAsynchro>(args.Holder());

			DataControle dataptUser;

			dataptUser.Output.PtUserwrapAsynchro = PtUserwrap;

			Output->push_back(dataptUser);

			Controle = true;

			return Output;
		}
	}
	return Output;
}
vector<DataControle>*              ControleUserAsynchro::ControleIsLoggedInAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
{
	Isolate* isolate = args.GetIsolate();

	vector<DataControle>* Output = NULL;

	if (ControleGetLenght(args, Message, 2)){
		if (ControleUserUnwrap(args, Message, 10) == true)
		{
			if (ControleSessionUnwrap(args, Message, 0) == true){

			Output = new vector<DataControle>();

			UserwrapAsynchro* PtUserwrap = ObjectWrap::Unwrap<UserwrapAsynchro>(args.Holder());

			DataControle dataptUser;

			dataptUser.Output.PtUserwrapAsynchro = PtUserwrap;

			Output->push_back(dataptUser);

			SessionwrapAsynchro* PtSessionwrap = ObjectWrap::Unwrap<SessionwrapAsynchro>(args[0]->ToObject());

			DataControle dataptSession;

			dataptSession.Output.PtSessionwrapAsynchro = PtSessionwrap;

			Output->push_back(dataptSession);

			Controle = true;

			return Output;
			}
		}
	}
	return Output;
}


}