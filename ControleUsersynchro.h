#pragma once
#include"ControleBasesynchro.h"
#include <node.h>
#include <node_object_wrap.h>
#include"v8.h"
#include"DataControlesyn.h"
#include<vector>
using namespace std;
namespace WaDirectory_Controle{
	class ControleUsersynchro :public ControleBasesynchro
	{
		static bool ControleValideUserData(IUser *PtUser, string& Message);
	public:
		ControleUsersynchro();
		~ControleUsersynchro();
		static vector<DataControlesyn>*              ControleGetNamesynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
		static vector<DataControlesyn>*              ControleBelongsToGroupwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message,int &Number);
		static vector<DataControlesyn>* 			 ControleGetDirectorywrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
		static vector<DataControlesyn>*              ControleIsLoggedInsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);
	};

}