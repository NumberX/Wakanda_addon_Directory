#pragma once
#include <node.h>
#include <node_object_wrap.h>
#include"v8.h"
namespace WaDirectorywrap_data_v8 {
	class ControleBasesynchro:public node::ObjectWrap
	{
	public:
		ControleBasesynchro();
		~ControleBasesynchro();

		static bool ControleGetLenght(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int Number);

		static bool ControleDirectoryUnwrap(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int indice);

		static bool ControleUserUnwrap(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int indice);

		static bool ControleSessionUnwrap(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int indice);

		static bool ControleGroupUnwrap(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int indice);

		static bool Controlestring(const v8::FunctionCallbackInfo<v8::Value>& args, std::string& Message, int number);

	};

}