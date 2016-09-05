#pragma once
#include"ControleBasesynchro.h"
#include <node.h>
#include <node_object_wrap.h>
#include"v8.h"
#include"DataControlesyn.h"
#include<vector>
using namespace std;
namespace WaDirectorywrap_data_v8{
	class ControleGroupsynchro: public WaDirectorywrap_data_v8::ControleBasesynchro
	{
	public:
		ControleGroupsynchro();

		~ControleGroupsynchro();

		static vector<DataControlesyn>* ControleGetNamesynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

		static vector<DataControlesyn>* ControleGetUserwrapByNamesynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

		static vector<DataControlesyn>* ControleGetSubGroupwrapNamesynchro(const v8::FunctionCallbackInfo<v8::Value>& args,bool& Controle, string& Message);

		static vector<DataControlesyn>* ControleGetDirectorywrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args,bool& Controle, string& Message);

	};

}