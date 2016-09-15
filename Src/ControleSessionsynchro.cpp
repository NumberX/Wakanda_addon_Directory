#include "ControleSessionsynchro.h"

namespace WaDirectory_Controle{
	ControleSessionsynchro::ControleSessionsynchro()
	{
	}


	ControleSessionsynchro::~ControleSessionsynchro()
	{
	}

	bool ControleSessionsynchro::ControleValideSessionData(ISession *PtSession, string& Message)
	{
		if (PtSession == NULL)
		{
			Message = "PtSession is Null";
			return false;
		}
		return true;

	}

	
		vector<DataControlesyn>*              ControleSessionsynchro::ControleGetsessionbase(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		vector<DataControlesyn>* Output = NULL;

		if (ControleGetLenght(args, Message, 0)){
			if (ControleSessionUnwrap(args, Message, 10) == true)
			{



				Sessionwrap* PtSessionwrap = ObjectWrap::Unwrap<Sessionwrap>(args.Holder());
				if (ControleValideSessionData(PtSessionwrap->GetSessionData(), Message))
				{
					Output = new vector<DataControlesyn>();

					DataControlesyn dataptsession;

					dataptsession.Output.PtSessionwrap = PtSessionwrap;

					Output->push_back(dataptsession);

					Controle = true;

					return Output;
				}
			}
		}
		return Output;
	}
		
	vector<DataControlesyn>*              ControleSessionsynchro::ControleGetUserwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		vector<DataControlesyn>* Output = NULL;

		if (ControleGetLenght(args, Message, 1)){
			if (ControleSessionUnwrap(args, Message, 10) == true)
			{

				

				Sessionwrap* PtSessionwrap = ObjectWrap::Unwrap<Sessionwrap>(args.Holder());
				if (ControleValideSessionData(PtSessionwrap->GetSessionData(), Message))
				{
					Output = new vector<DataControlesyn>();

					DataControlesyn dataptsession;

					dataptsession.Output.PtSessionwrap = PtSessionwrap;

					Output->push_back(dataptsession);

					Controle = true;

					return Output;
				}
			}
		}
		return Output;
	}
vector<DataControlesyn>*              ControleSessionsynchro::ControleGetWASIDsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
{
	return ControleGetsessionbase(args, Controle, Message);
}
vector<DataControlesyn>* 			 ControleSessionsynchro::ControleGetDirectorywrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
{
	return ControleGetsessionbase(args, Controle, Message);
}
vector<DataControlesyn>*              ControleSessionsynchro::ControleIsValidsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
{
	return ControleGetUserwrapsynchro(args, Controle, Message);
}
vector<DataControlesyn>*              ControleSessionsynchro::ControleLogOutsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
{
	return ControleGetsessionbase(args, Controle, Message);
}

}