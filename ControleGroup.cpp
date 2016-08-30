#include"ControleGroup.h"
#include <node.h>
#include"Utility.h"
#include<vector>
#include<string>


using namespace Controle;
namespace Controle{


ControleGroup::ControleGroup()
{}
ControleGroup::~ControleGroup()
{

}
bool ControleGroup::ControleGetLenght(const v8::FunctionCallbackInfo<v8::Value>& args,  std::string &Message, int Number)
{
	if (args.Length() == Number) {


		return true;


	}
	

		Message = "Wrong number of argument";

		return false;

	

}
bool ControleGroup::GetUserwrapByName(const v8::FunctionCallbackInfo<v8::Value>& args, IGroup *ptgroup, std::string &Message, int Number)
{
	bool Resultat = ControlePtGroup(ptgroup, Message);

	Resultat = this->ControleGetLenght(args, Message, 2);

	for (int Iterator = 0; Iterator < Number; Iterator++)
		Resultat = this->ControleGetType(args, Message, Iterator);

	return Resultat;

}
bool ControleGroup::ControleGetType(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int Number)
{

	if ((args[Number]->IsString()))
	{
		return true;
	}


	Message = "the argument need to be string value";

	return false;

}
bool ControleGroup::ControleGet(const v8::FunctionCallbackInfo<v8::Value>& args, IGroup* PtGroup, std::string &Message)
{
	Isolate* isolate = args.GetIsolate();

	bool Resultat=ControlePtGroup(PtGroup, Message);
	if ( Resultat== true)
	{
		if (args.Length() == 1) {


			if ((args[0]->IsString()))
			{
				return true;
			}
			else
			{
				Message = "the argument need to be string value";

			}

		}
		else if (args.Length() != 1) {

			Message = "Wrong number of argument";


		}

	}
	else
	{
		return false;
	}
	return false;

}
bool ControleGroup::ControlePtGroup(IGroup* PtGroup, std::string &Message)
{
	if (PtGroup != NULL)
	{
		return true;
	}


	
	Message = "the Group Object is NULL Value";

	return false;
}


}