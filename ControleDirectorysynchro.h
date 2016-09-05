#ifndef ControleDirectorysynchro_H
#define ControleDirectorysynchro_H
#include"ControleBasesynchro.h"
#include <node.h>
#include <node_object_wrap.h>
#include"v8.h"
#include"DataControlesyn.h"
#include<vector>
using namespace std;
namespace WaDirectorywrap_data_v8{
	class ControleDirectorysynchro : public WaDirectorywrap_data_v8::ControleBasesynchro {
	
private:

	static vector<DataControlesyn>* ControleGetGroupssynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControlesyn>* ControleGetGroupSessionsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

public:

	ControleDirectorysynchro();

	~ControleDirectorysynchro();

	static vector<DataControlesyn>* ControleLogInsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle,string& Message);

	static vector<DataControlesyn>* ControleLogOutsynchro1(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, std::string& Message);

	static vector<DataControlesyn>* ControleGetGroupwrapIDsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControlesyn>* ControleGetGroupwrapNamessynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControlesyn>* ControleGetGroupwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControlesyn>* ControleGetSessionwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControlesyn>*  ControleGetUserwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControlesyn>*  ControleUserwrapBelongTosynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message, int& MethodeNumber);
	};
}
#endif;