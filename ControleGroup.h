#ifndef ControleGroup_H
#define ControleGroup_H
#include"Groupwrap.h"
#include<v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include<stdbool.h>

using namespace WaDirectorywrap_data_v8;
using v8::Exception;
using namespace v8;
using namespace std;
namespace Controle{
class ControleGroup
{
private :
	
public:
ControleGroup();
~ControleGroup();
bool ControleGet(const v8::FunctionCallbackInfo<v8::Value>& args, Group* PtDirectory, std::string &Message);
bool ControlePtGroup(Group* PtGroup, std::string &Message);
bool ControleGetLenght(const v8::FunctionCallbackInfo<v8::Value>& args,  std::string &Message, int Number);
bool ControleGetType(const v8::FunctionCallbackInfo<v8::Value>& args,  std::string &Message, int Number);
bool GetUserwrapByName(const v8::FunctionCallbackInfo<v8::Value>& args,Group *ptgroup, std::string &Message, int Number);
};



}
#endif