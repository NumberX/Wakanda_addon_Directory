#ifndef ControleUser_H
#define ControleUser_H
#include"Directorywrap.h"
#include<v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include<stdbool.h>
#include"ControleUser.h"
using namespace WaDirectorywrap_data_v8;
using v8::Exception;
using namespace v8;
using namespace std;
namespace Controle{
class ControleUser
{
private :

public:
ControleUser();
~ControleUser();


bool ControleGetLenght(const v8::FunctionCallbackInfo<v8::Value>& args,std::string &Message, int Number);

bool ControleGetType(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int Number);

bool ControleGetPtUser(const v8::FunctionCallbackInfo<v8::Value>& args, IUser* PtUser, std::string &Message);

};



}
#endif