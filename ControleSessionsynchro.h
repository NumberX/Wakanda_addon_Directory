#pragma once
#include"ControleBasesynchro.h"
#include <node.h>
#include <node_object_wrap.h>
#include"v8.h"
#include"DataControlesyn.h"
#include<vector>
using namespace std;
namespace WaDirectorywrap_data_v8{
	class ControleSessionsynchro : public WaDirectorywrap_data_v8::ControleBasesynchro
	{
	public:
		ControleSessionsynchro();
		~ControleSessionsynchro();
static vector<DataControlesyn>*              ControleGetUserwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
static vector<DataControlesyn>*              ControleGetWASIDsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
static vector<DataControlesyn>* 			 ControleGetDirectorywrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
static vector<DataControlesyn>*              ControleIsValidsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
static vector<DataControlesyn>*              ControleLogOutsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
	};

}