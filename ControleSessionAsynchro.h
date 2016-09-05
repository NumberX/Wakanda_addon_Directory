#pragma once
#include"ControleBaseAsynchro.h"
#include <node.h>
#include <node_object_wrap.h>
#include"v8.h"
#include"DataControle.h"
#include<vector>
using namespace std;
namespace WaDirectorywrapAsynchro_data_v8{
	class ControleSessionAsynchro :public WaDirectorywrapAsynchro_data_v8::ControleBaseAsynchro
	{
	public:
		ControleSessionAsynchro();
		~ControleSessionAsynchro();
		static vector<DataControle>*              ControleGetUserwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
		static vector<DataControle>*              ControleGetWASIDAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
		static vector<DataControle>* 			 ControleGetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
		static vector<DataControle>*              ControleIsValidAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
		static vector<DataControle>*              ControleLogOutAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	};

}