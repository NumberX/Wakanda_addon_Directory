#include"ControleSession.h"
#include <node.h>
#include"Utility.h"
#include<vector>
#include<string>


using namespace Controle;
namespace Controle{


ControleSession::ControleSession()
{}
ControleSession::~ControleSession()
{

}

bool ControleSession::ControlePtSession(Session* PtSession, std::string &Message)
{
	if (PtSession != NULL)
	{
		return true;
	}


	Message = "the Session Object is NULL Value";

	return false;
}
bool ControleSession::ControleGetLenght(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int Number)
{
	if (args.Length() == Number) {

		return true;

	}


	Message = "Wrong number of argument";

	return false;



}

}