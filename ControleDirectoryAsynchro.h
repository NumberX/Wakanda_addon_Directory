#ifndef ControleDirectoryAsynchro_H
#define ControleDirectoryAsynchro_H
#include"ControleBaseAsynchro.h"
#include <node.h>
#include <node_object_wrap.h>
#include"v8.h"
#include"DataControle.h"
#include<vector>
using namespace std;
namespace WaDirectorywrapAsynchro_data_v8{
	class ControleDirectoryAsynchro : public WaDirectorywrapAsynchro_data_v8::ControleBaseAsynchro {
	
private:

	static vector<DataControle>* ControleGetGroups(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControle>* ControleGetGroupSession(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

public:

	ControleDirectoryAsynchro();

	~ControleDirectoryAsynchro();

	static vector<DataControle>* ControleLogInAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle,string& Message);

	static vector<DataControle>* ControleLogOutAsynchro1(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, std::string& Message);

	static vector<DataControle>* ControleGetGroupwrapIDAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControle>* ControleGetGroupwrapNamesAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControle>* ControleGetGroupwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControle>* ControleGetSessionwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControle>*  ControleGetUserwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControle>*  ControleUserwrapBelongToAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message, int& MethodeNumber);
	};
}
#endif;