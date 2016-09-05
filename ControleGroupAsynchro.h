#pragma once
#include"ControleBaseAsynchro.h"
#include <node.h>
#include <node_object_wrap.h>
#include"v8.h"
#include"DataControle.h"
#include<vector>
using namespace std;
namespace WaDirectorywrapAsynchro_data_v8{
	class ControleGroupAsynchro : public WaDirectorywrapAsynchro_data_v8::ControleBaseAsynchro
	{
	public:
		ControleGroupAsynchro();

		~ControleGroupAsynchro();

		static vector<DataControle>* ControleGetNameAsynchro2(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

		static vector<DataControle>* ControleGetUserwrapByNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args,  bool& Controle, string& Message);
		
		static vector<DataControle>* ControleGetSubGroupwrapNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args,  bool& Controle, string& Message);
		
		static vector<DataControle>* ControleGetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
	};

}