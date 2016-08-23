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
bool ControleUser::ControleUserUnwrap(Handle<Object> handle, v8::Persistent<v8::Value> prototype)
{
	if (!handle.IsEmpty() && handle->InternalFieldCount() == 1) {

		Handle<Value> objproto = handle->GetPrototype();
		if (objproto == prototype) {

			return true;
		}
	}

	return false;
}



}