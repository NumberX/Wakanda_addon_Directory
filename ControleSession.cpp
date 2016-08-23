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
	else
	{

		Message = "the Directory Object is NULL Value";

	}
	return false;
}


}