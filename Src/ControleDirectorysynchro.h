#ifndef ControleDirectorysynchro_H
#define ControleDirectorysynchro_H
#include"ControleBasesynchro.h"
#include"IDirectory.h"
#include <node.h>
#include <node_object_wrap.h>
#include"v8.h"
#include"DataControlesyn.h"
#include<vector>
using namespace v8;
using namespace std;
using namespace WaDirectory_Data;
namespace WaDirectory_Controle{
	class DataControlesyn;
	class ControleDirectorysynchro : public ControleBasesynchro {
	
private:

	static bool ControleDirectorysynchro::valide(string Phrase);

	static vector<DataControlesyn>* ControleGetGroupssynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControlesyn>* ControleGetGroupSessionsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static bool ControleValideDirectoryData(IDirectory *PtDirectory,string& Message);

public:

	ControleDirectorysynchro();

	~ControleDirectorysynchro();

	static vector<DataControlesyn>* ControleLogInsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle,string& Message);

	static vector<DataControlesyn>* ControleLogOutsynchro1(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, std::string& Message);

	static vector<DataControlesyn>* ControleGetGroupwrapIDsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControlesyn>* ControleGetGroupwrapNamessynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControlesyn>* ControleGetGroupwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControlesyn>* ControleGetSessionwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message,int& Methode);

	static vector<DataControlesyn>*  ControleGetUserwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message);

	static vector<DataControlesyn>*  ControleUserwrapBelongTosynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message, int& MethodeNumber);
	};
}
#endif;