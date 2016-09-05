#include "ControleSessionsynchro.h"
#include<iostream>
namespace WaDirectorywrap_data_v8{
	ControleSessionsynchro::ControleSessionsynchro()
	{
	}


	ControleSessionsynchro::~ControleSessionsynchro()
	{
	}

	vector<DataControlesyn>*    ControleSessionsynchro::ControleGetUserwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		vector<DataControlesyn>* Output = NULL;


		if (ControleGetLenght(args, Message, 0)){
			if (ControleSessionUnwrap(args, Message, 10) == true)
			{

				Output = new vector<DataControlesyn>();

				Sessionwrap* PtSessionwrap = ObjectWrap::Unwrap<Sessionwrap>(args.Holder()->ToObject());

				DataControlesyn dataptsession;

				dataptsession.Output.PtSessionwrap = PtSessionwrap;

				Output->push_back(dataptsession);

				Controle = true;
			}
		}
		return Output;
	}
	vector<DataControlesyn>*              ControleSessionsynchro::ControleGetWASIDsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		return NULL;
	}
	vector<DataControlesyn>* 			 ControleSessionsynchro::ControleGetDirectorywrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		return NULL;
	}
	vector<DataControlesyn>*              ControleSessionsynchro::ControleIsValidsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		return NULL;
	}
	vector<DataControlesyn>*              ControleSessionsynchro::ControleLogOutsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		return NULL;
	}

}
