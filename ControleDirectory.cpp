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

bool ControleDirectory::ControleGetLenght(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int Number)
{
	if (args.Length() == Number) {

	
		return true;


	}
	

		Message = "Wrong number of argument";

		return false;



}

bool ControleDirectory::ControleGetType(const v8::FunctionCallbackInfo<v8::Value>& args,  std::string &Message, int Number)
{

		if ((args[Number]->IsString()))
		{
			return true;
		}

			
		Message = "the argument need to be string value";

		return false;

}
bool ControleDirectory::ControleGetPtDirectory(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message, int Number)
{
	if (PtDirectory != NULL)
	{
		return true;
	}

	Message = "the Directory Object is NULL Value";

	return false;
}
bool ControleDirectory::ControleLogIn(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message)
{
	Isolate* isolate = args.GetIsolate();
	
	return ControleGet(args, PtDirectory, Message, 2);

}

bool ControleDirectory::ControleGetGroupwrapNames(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message)
{
	Isolate* isolate = args.GetIsolate();

	return ControleGetPtDirectory(args, PtDirectory, Message, 1);
	
}


bool ControleDirectory::ControleGet(const v8::FunctionCallbackInfo<v8::Value>& args, Directory* PtDirectory, std::string &Message,int Number)
{
	Isolate* isolate = args.GetIsolate();

	bool Resultat = ControleGetPtDirectory(args, PtDirectory, Message, Number);

	if (Resultat)
	{
		Resultat=ControleGetLenght(args,  Message, Number);

		if (Resultat) {
		
			for (int Iterator = 0; Iterator < Number; Iterator++)
			{
				Resultat = this->ControleGetType(args,  Message,Iterator );
		
			}
			if (Resultat)
			{
				return true;
			}
			else
			{
				return false;

			}

		}
		else  {

			return false;


		}

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