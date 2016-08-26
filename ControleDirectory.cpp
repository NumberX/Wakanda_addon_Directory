#include"ControleDirectory.h"
#include <node.h>
#include"Utility.h"
#include<vector>
#include<string>


using namespace Controle;
namespace Controle{


ControleDirectory::ControleDirectory()
{}
ControleDirectory::~ControleDirectory()
{

}

bool ControleDirectory::ControleLogIn(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message)
{
	Isolate* isolate = args.GetIsolate();
	
	if (PtDirectory != NULL)
	{
		if (args.Length() == 2) {


			if ((args[0]->IsString()) && (args[1]->IsString()))
			{
				return true;
			}
			else
			{
				Message="the arguments need to be string value";
				
			}

		}
		else if(args.Length() != 2) {

			Message = "Wrong number of arguments";


		}

	}
	else
	{
		Message = "the Directory Object is NULL Value";
	}
	return false;

}

bool ControleDirectory::ControleGetGroupwrapNames(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message)
{
	Isolate* isolate = args.GetIsolate();

	if (PtDirectory == NULL)
	{
		
		Message = "the Directory Object is NULL Value";
		return false;
	}
	
	return true;


}
bool ControleDirectory::ControleGet(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message,int Number)
{
	Isolate* isolate = args.GetIsolate();

	if (PtDirectory != NULL)
	{
		if (args.Length() == Number) {


			if ((args[0]->IsString()))
			{
				return true;
			}
			else
			{
				Message = "the argument need to be string value";

			}

		}
		else if (args.Length() != Number) {

			Message = "Wrong number of argument";


		}

	}
	else
	{
		Message = "the Directory Object is NULL Value";
	}
	return false;

}
bool ControleDirectory::ControleGetGroupwrap(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message)
{

	return (this->ControleGet(args, PtDirectory, Message,1));
}
bool ControleDirectory::ControleGetUserwrap(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message)
{
	return (this->ControleGet(args, PtDirectory, Message,2));

}
bool ControleDirectory::ControleGetSessionwrap(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message)
{
	return (this->ControleGet(args, PtDirectory, Message,1));
}



}