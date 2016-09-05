#pragma once
#include"ControleBaseAsynchro.h"
#include <node.h>
#include <node_object_wrap.h>
#include"v8.h"
#include"DataControle.h"
#include<vector>
using namespace std;
namespace WaDirectorywrapAsynchro_data_v8{
	class ControleUserAsynchro :public WaDirectorywrapAsynchro_data_v8::ControleBaseAsynchro
	{
	public:
		ControleUserAsynchro();
		~ControleUserAsynchro();
		static vector<DataControle>*              ControleGetNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
		static vector<DataControle>*              ControleBelongsToGroupwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message,int &Number);
		static vector<DataControle>* 			 ControleGetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
		static vector<DataControle>*              ControleIsLoggedInAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
	};

}