#include "ControleGroupsynchro.h"
#include"Utility.h"
namespace WaDirectorywrap_data_v8{

	ControleGroupsynchro::ControleGroupsynchro()
	{
	}


	ControleGroupsynchro::~ControleGroupsynchro()
	{
	}

	vector<DataControlesyn>* ControleGroupsynchro::ControleGetNamesynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControlesyn>* Output = NULL;

		if (ControleGetLenght(args, Message, 0))
		{
			if (ControleGroupUnwrap(args, Message, 10) == true)
			{
				Output = new vector<DataControlesyn>();

				Groupwrap* PtGroupwrap = ObjectWrap::Unwrap<Groupwrap>(args.Holder());

				DataControlesyn dataptgroup;

				dataptgroup.Output.PtGroupwrap = PtGroupwrap;

				Output->push_back(dataptgroup);

				Controle = true;
			}
		}
		return Output;
	}
	vector<DataControlesyn>* ControleGroupsynchro::ControleGetUserwrapByNamesynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{

		vector<DataControlesyn>* Output = NULL;

		if (ControleGetLenght(args, Message, 2)){
			if (ControleGroupUnwrap(args, Message, 10) == true)
			{
				if (Controlestring(args, Message, 0) == true)
				{
					if (Controlestring(args, Message, 1) == true)
					{

						Output = new vector<DataControlesyn>();

						Groupwrap* PtGroupwrap = ObjectWrap::Unwrap<Groupwrap>(args.Holder());

						DataControlesyn dataptgroup;

						dataptgroup.Output.PtGroupwrap = PtGroupwrap;

						Output->push_back(dataptgroup);

						Utility util;

						string UserId = util.V8Utf8ValueToStdString(args[0]);

						DataControlesyn ddatauser;

						ddatauser.Output.UserId = new char[UserId.length() + 1];;

						std::strcpy(ddatauser.Output.UserId, UserId.c_str());

						Output->push_back(ddatauser);

						string passwordId = util.V8Utf8ValueToStdString(args[1]);

						DataControlesyn ddatapassword;

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
	vector<DataControlesyn>* ControleGroupsynchro::ControleGetSubGroupwrapNamesynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControlesyn>* Output = NULL;

		if (ControleGetLenght(args, Message, 0))
		{
			if (ControleGroupUnwrap(args, Message, 10) == true)
			{
				Output = new vector<DataControlesyn>();

				Groupwrap* PtGroupwrap = ObjectWrap::Unwrap<Groupwrap>(args.Holder());

				DataControlesyn dataptgroup;

				dataptgroup.Output.PtGroupwrap = PtGroupwrap;

				Output->push_back(dataptgroup);

				Controle = true;
			}
		}
		return Output;
	}
	vector<DataControlesyn>* ControleGroupsynchro::ControleGetDirectorywrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControlesyn>* Output = NULL;

		if (ControleGetLenght(args, Message, 0))
		{
			if (ControleGroupUnwrap(args, Message, 10) == true)
			{
				Output = new vector<DataControlesyn>();

				Groupwrap* PtGroupwrap = ObjectWrap::Unwrap<Groupwrap>(args.Holder());

				DataControlesyn dataptgroup;

				dataptgroup.Output.PtGroupwrap = PtGroupwrap;

				Output->push_back(dataptgroup);

				Controle = true;
			}
		}
		return Output;
	}
}