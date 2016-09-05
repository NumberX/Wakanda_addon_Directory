#include "ControleGroupAsynchro.h"
#include<iostream>
namespace WaDirectorywrapAsynchro_data_v8{
	ControleGroupAsynchro::ControleGroupAsynchro()
	{
	}


	ControleGroupAsynchro::~ControleGroupAsynchro()
	{
	}

	vector<DataControle>* ControleGroupAsynchro::ControleGetNameAsynchro2(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		vector<DataControle>* Output = NULL;

		if (ControleGetLenght(args, Message, 1)){
			if (ControleGroupUnwrap(args, Message, 10) == true)
			{
				
				Output = new vector<DataControle>();

				GroupwrapAsynchro* PtGroupwrap = ObjectWrap::Unwrap<GroupwrapAsynchro>(args.Holder());

				DataControle dataptgroup;

				dataptgroup.Output.PtGroupwrapAsynchro = PtGroupwrap;

				Output->push_back(dataptgroup);

				Controle = true;

				return Output;
			}
		}
		return Output;
	}
	vector<DataControle>* ControleGroupAsynchro::ControleGetUserwrapByNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		vector<DataControle>* Output = NULL;

		if (ControleGetLenght(args, Message, 3)){
			if (ControleGroupUnwrap(args, Message, 10) == true)
			{
				if (Controlestring(args, Message, 0) == true)
				{
					if (Controlestring(args, Message, 1) == true)
					{

						Output = new vector<DataControle>();

						GroupwrapAsynchro* PtGroupwrap = ObjectWrap::Unwrap<GroupwrapAsynchro>(args.Holder());

						DataControle dataptgroup;

						dataptgroup.Output.PtGroupwrapAsynchro = PtGroupwrap;

						Output->push_back(dataptgroup);

						Utility util;

						string UserId = util.V8Utf8ValueToStdString(args[0]);

						DataControle ddatauser;

						ddatauser.Output.UserId = new char[UserId.length() + 1];;

						std::strcpy(ddatauser.Output.UserId, UserId.c_str());

						Output->push_back(ddatauser);

						string passwordId = util.V8Utf8ValueToStdString(args[1]);

						DataControle ddatapassword;

						ddatapassword.Output.Password = new char[passwordId.length() + 1];;

						std::strcpy(ddatapassword.Output.Password, passwordId.c_str());

						Output->push_back(ddatapassword);

						Controle = true;

						return Output;
					}
				}
			}
		}
		return Output;
	}
	vector<DataControle>* ControleGroupAsynchro::ControleGetSubGroupwrapNameAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args,  bool& Controle, string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		vector<DataControle>* Output = NULL;

		if (ControleGetLenght(args, Message, 1)){
			if (ControleGroupUnwrap(args, Message, 10) == true)
			{

				Output = new vector<DataControle>();

				GroupwrapAsynchro* PtGroupwrap = ObjectWrap::Unwrap<GroupwrapAsynchro>(args.Holder());

				DataControle dataptgroup;

				dataptgroup.Output.PtGroupwrapAsynchro = PtGroupwrap;

				Output->push_back(dataptgroup);

				Controle = true;

				return Output;
			}
		}
		return Output;
	}
	vector<DataControle>* ControleGroupAsynchro::ControleGetDirectorywrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		vector<DataControle>* Output = NULL;

		if (ControleGetLenght(args, Message, 1)){
			if (ControleGroupUnwrap(args, Message, 10) == true)
			{

				Output = new vector<DataControle>();

				GroupwrapAsynchro* PtGroupwrap = ObjectWrap::Unwrap<GroupwrapAsynchro>(args.Holder());

				DataControle dataptgroup;

				dataptgroup.Output.PtGroupwrapAsynchro = PtGroupwrap;

				Output->push_back(dataptgroup);

				Controle = true;

				return Output;
			}
		}
		return Output;
	}

}