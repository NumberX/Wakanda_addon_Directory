#ifndef ControleUser_H
#define ControleUser_H
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
class ControleUser
{
private :

public:
ControleUser();
~ControleUser();
bool ControleUserUnwrap(Handle<Object> handle, v8::Persistent<v8::Value> prototype);

};



}
#endif