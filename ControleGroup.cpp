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
bool ControleGroup::ControleGet(const v8::FunctionCallbackInfo<v8::Value>& args, Group* PtGroup, std::string &Message)
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
bool ControleGroup::ControlePtGroup(Group* PtGroup, std::string &Message)
{
	if (PtGroup != NULL)
	{
		return true;
	}
	else
	{

		Message = "the Directory Object is NULL Value";

	}
	return false;
}


}