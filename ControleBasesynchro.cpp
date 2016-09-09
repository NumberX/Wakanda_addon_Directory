#include "ControleBasesynchro.h"
#include"Directorywrap.h"
#include"Groupwrap.h"
#include"Userwrap.h"
#include"Sessionwrap.h"
#include"Utility.h"
#include <node.h>
#include <node_object_wrap.h>
#include<iostream>
using namespace WaDirectory_View;
namespace WaDirectory_Controle {
	ControleBasesynchro::ControleBasesynchro()
	{
	}


	ControleBasesynchro::~ControleBasesynchro()
	{
	}




	bool ControleBasesynchro::ControleGetLenght(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int Number)
	{
		if (args.Length() == Number) {


			return true;


		}


		Message = "Wrong number of argument";

		return false;



	}

	bool ControleBasesynchro::ControleDirectoryUnwrap(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int indice)
	{
		



		Isolate* isolate = args.GetIsolate();
		if (indice == 10)
		{
			if (Directorywrap::ControleDirectoryUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
			{


				Message = "this is not a Directory object";

				return false;

			}		
			return true;
		}
		if (Directorywrap::ControleDirectoryUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
		{


			Message = "this is not a Directory object";

			return false;

		}
		return true;
	}

	bool ControleBasesynchro::ControleUserUnwrap(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int indice)
	{
		Isolate* isolate = args.GetIsolate();
		if (indice == 10)
		{
			if (Userwrap::ControleUserUnwrap(args.Holder(), isolate)->BooleanValue() == false)
			{


				Message = "the argument need to be Userobject";

				return false;

			}
			return true;
		}

		if (Userwrap::ControleUserUnwrap(args[indice]->ToObject(), isolate)->BooleanValue() == false)
		{
			Message = "the argument need to be Userobject";

			return false;
		}
		return true;
	}

	bool ControleBasesynchro::ControleGroupUnwrap(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int indice)
	{
		Isolate* isolate = args.GetIsolate();
		if (indice == 10)
		{
			if (Groupwrap::ControleGroupUnwrap(args.Holder(), isolate)->BooleanValue() == false)
			{
				Message = "the argument need to be Groupobject";

				return false;
			}
			return true;

		}
		if (Groupwrap::ControleGroupUnwrap(args[indice]->ToObject(), isolate)->BooleanValue() == false)
		{
			Message = "the argument need to be Groupobject";

			return false;
		}
		return true;
	}

	bool ControleBasesynchro::ControleSessionUnwrap(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int indice)
	{
		Isolate* isolate = args.GetIsolate();
		if (indice == 10)
		{
			if (Sessionwrap::ControleSessionUnwrap(args.Holder(), isolate)->BooleanValue() == false)
			{
				Message = "the argument need to be Sessionobject";

				return false;
			}
			return true;

		}

		if (Sessionwrap::ControleSessionUnwrap(args[indice]->ToObject(), isolate)->BooleanValue() == false)
		{
			Message = "the argument need to be Sessionobject";

			return false;
		}
		return true;
	}


	bool ControleBasesynchro::Controlestring(const v8::FunctionCallbackInfo<v8::Value>& args, std::string& Message, int number)
	{
		Isolate* isolate = args.GetIsolate();

		if (args[number]->IsString())
		{
			return true;
		}
		else
		{
			Message = "the argument " + to_string(number) + " need to be string ";
			return false;
		}
	}

}