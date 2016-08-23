#ifndef ControleSession_H
#define ControleSession_H
#include"Sessionwrap.h"
#include<v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include<stdbool.h>

using namespace WaDirectorywrap_data_v8;
using v8::Exception;
using namespace v8;
using namespace std;
namespace Controle{
class ControleSession
{
private :
	
public:
ControleSession();
~ControleSession();
bool ControlePtSession(Session* PtSession, std::string &Message);

};



}
#endif