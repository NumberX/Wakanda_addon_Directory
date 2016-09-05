#include "ControleSessionAsynchro.h"

namespace WaDirectorywrapAsynchro_data_v8{
	ControleSessionAsynchro::ControleSessionAsynchro()
	{
	}


	ControleSessionAsynchro::~ControleSessionAsynchro()
	{
	}

	vector<DataControle>*              ControleSessionAsynchro::ControleGetUserwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		vector<DataControle>* Output = NULL;

		if (ControleGetLenght(args, Message, 1)){
			if (ControleSessionUnwrap(args, Message, 10) == true)
			{

				Output = new vector<DataControle>();

				SessionwrapAsynchro* PtSessionwrap = ObjectWrap::Unwrap<SessionwrapAsynchro>(args.Holder());

				DataControle dataptsession;

				dataptsession.Output.PtSessionwrapAsynchro = PtSessionwrap;

				Output->push_back(dataptsession);

				Controle = true;

				return Output;
			}
		}
		return Output;
	}
vector<DataControle>*              ControleSessionAsynchro::ControleGetWASIDAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
{
	return ControleGetUserwrapAsynchro(args,Controle,Message);
}
vector<DataControle>* 			 ControleSessionAsynchro::ControleGetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
{
	return ControleGetUserwrapAsynchro(args, Controle, Message);
}
vector<DataControle>*              ControleSessionAsynchro::ControleIsValidAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
{
	return ControleGetUserwrapAsynchro(args, Controle, Message);
}
vector<DataControle>*              ControleSessionAsynchro::ControleLogOutAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
{
	return ControleGetUserwrapAsynchro(args, Controle, Message);
}

}