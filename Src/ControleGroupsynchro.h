#pragma once
#include"ControleBasesynchro.h"
#include <node.h>
#include <node_object_wrap.h>
#include"v8.h"
#include"DataControlesyn.h"
#include<vector>
#include"IGroup.h"
using namespace WaDirectory_Data;
using namespace std;
namespace WaDirectory_Controle{
	class DataControlesyn;
	class ControleGroupsynchro : public ControleBasesynchro
	{
		static bool ControleValideGroupData(IGroup *PtGroup, string& Message);

	public:
		ControleGroupsynchro();

		~ControleGroupsynchro();

		static vector<DataControlesyn>* ControleGetNamesynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

		static vector<DataControlesyn>* ControleGetUserwrapByNamesynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

		static vector<DataControlesyn>* ControleGetSubGroupwrapNamesynchro(const v8::FunctionCallbackInfo<v8::Value>& args,bool& Controle, string& Message);

		static vector<DataControlesyn>* ControleGetDirectorywrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args,bool& Controle, string& Message);

	};

}