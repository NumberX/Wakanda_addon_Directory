#include "ControleBaseAsynchro.h"
#include"DirectorywrapAsynchro.h"
#include"Utility.h"
#include <node.h>
#include <node_object_wrap.h>
using namespace WaDirectorywrapAsynchro_data_v8;
namespace WaDirectorywrapAsynchro_data_v8{
	ControleBaseAsynchro::ControleBaseAsynchro()
	{
	}


	ControleBaseAsynchro::~ControleBaseAsynchro()
	{
	}

	bool ControleBaseAsynchro::ControleGetLenght(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int Number)
	{
		if (args.Length() == Number) {


			return true;


		}


		Message = "Wrong number of argument";

		return false;



	}

	bool ControleBaseAsynchro::ControleDirectoryUnwrap(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message,int indice)
	{
		Isolate* isolate = args.GetIsolate();
		if (indice == 10)
		{
			if (DirectorywrapAsynchro::ControleDirectoryUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
			{


				Message = "this is not a Directory object";

				return false;

			}
			return true;
		}
		if (DirectorywrapAsynchro::ControleDirectoryUnwrap(args.Holder()->ToObject(), isolate)->BooleanValue() == false)
		{


			Message = "this is not a Directory object";

			return false;

		}
		return true;
	}

	bool ControleBaseAsynchro::ControleUserUnwrap(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int indice)
	{
		Isolate* isolate = args.GetIsolate();
		if (indice == 10)
		{
			if (UserwrapAsynchro::ControleUserUnwrap(args.Holder(), isolate)->BooleanValue() == false)
			{


				Message = "the argument need to be Userobject";

				return false;

			}
			return true;
		}

		if (UserwrapAsynchro::ControleUserUnwrap(args[indice]->ToObject(), isolate)->BooleanValue() == false)
		{
			Message = "the argument need to be Userobject";

			return false;
		}
		return true;
	}

	bool ControleBaseAsynchro::ControleGroupUnwrap(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int indice)
	{
		Isolate* isolate = args.GetIsolate();
		if (indice == 10)
		{

			if (GroupwrapAsynchro::ControleGroupUnwrap(args.Holder(), isolate)->BooleanValue() == false)
			{
				Message = "the argument need to be Groupobject 12";

				return false;
			}

			return true;

		}
		if (GroupwrapAsynchro::ControleGroupUnwrap(args[indice]->ToObject(), isolate)->BooleanValue() == false)
		{
			Message = "the argument need to be Groupobject";

			return false;
		}
		return true;
	}

	bool ControleBaseAsynchro::ControleSessionUnwrap(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int indice)
	{
		Isolate* isolate = args.GetIsolate();
		if (indice == 10)
		{
			if (SessionwrapAsynchro::ControleSessionUnwrap(args.Holder(), isolate)->BooleanValue() == false)
			{
				Message = "the argument need to be Sessionobject";

				return false;
			}
			return true;

		}

		if (SessionwrapAsynchro::ControleSessionUnwrap(args[indice]->ToObject(), isolate)->BooleanValue() == false)
		{
			Message = "the argument need to be Sessionobject";

			return false;
		}
		return true;
	}


	bool ControleBaseAsynchro::Controlestring(const v8::FunctionCallbackInfo<v8::Value>& args, std::string& Message, int number)
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
