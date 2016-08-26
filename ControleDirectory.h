#ifndef ControleDirectory_H
#define ControleDirectory_H
#include"Directorywrap.h"
#include<v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include<stdbool.h>

using namespace WaDirectorywrap_data_v8;
using v8::Exception;
using namespace v8;
using namespace std;
namespace Controle{
class ControleDirectory
{
private :
	bool ControleGet(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message,int Number);
public:
ControleDirectory();
~ControleDirectory();

bool ControleLogIn(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &error);
bool ControleGetGroupwrapNames(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message);
bool ControleGetGroupwrap(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message);
bool ControleGetUserwrap(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message);
bool ControleGetSessionwrap(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message);

};



}
#endif