#include"ControleUser.h"
#include <node.h>
#include"Utility.h"
#include<vector>
#include<string>


using namespace Controle;
namespace Controle{


ControleUser::ControleUser()
{}
ControleUser::~ControleUser()
{

}

bool ControleUser::ControleGetLenght(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int Number)
{
	if (args.Length() == Number) {

		return true;

	}


	Message = "Wrong number of argument";

	return false;

}

bool ControleUser::ControleGetType(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int Number)
{
	if ((args[Number]->IsString()))
	{
		return true;
	}


	Message = "the argument need to be string value";

	return false;

}

bool ControleUser::ControleGetPtUser(const v8::FunctionCallbackInfo<v8::Value>& args, User* PtUser, std::string &Message)
{
	if (PtUser != NULL)
	{
		return true;
	}

	Message = "the User Object is NULL Value";

	return false;
}
}