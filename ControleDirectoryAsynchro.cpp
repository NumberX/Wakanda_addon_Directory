#include"ControleDirectoryAsynchro.h"
#include"DirectorywrapAsynchro.h"
#include"ControleBaseAsynchro.h"
#include"Utility.h"
#include <node.h>
#include <node_object_wrap.h>
#include<iostream>
using namespace WaDirectorywrapAsynchro_data_v8;
namespace WaDirectorywrapAsynchro_data_v8{
	ControleDirectoryAsynchro::ControleDirectoryAsynchro(){
	
	}
	ControleDirectoryAsynchro::~ControleDirectoryAsynchro(){
	
	
	}

	/*
	bool ControleDirectoryAsynchro::ControleGetLenght(const v8::FunctionCallbackInfo<v8::Value>& args, std::string &Message, int Number)
	{
		if (args.Length() == Number) {


			return true;


		}


		Message = "Wrong number of argument";

		return false;



	}

	*/

	vector<DataControle>* ControleDirectoryAsynchro::ControleLogOutAsynchro1(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, std::string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControle>* Output=NULL;

		if (ControleGetLenght(args, Message, 2))
		{
			if (ControleDirectoryUnwrap(args, Message,10) == true)
			{
				Output = new vector<DataControle>();

				DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

				DataControle dataptdirectory;

				dataptdirectory.Output.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

				Output->push_back(dataptdirectory);

				if (ControleSessionUnwrap(args, Message,0) == true)
				{
					SessionwrapAsynchro* PtSessionWrap = ObjectWrap::Unwrap<SessionwrapAsynchro>(args[0]->ToObject());

					DataControle dataptsession;

					dataptsession.Output.PtSessionwrapAsynchro = PtSessionWrap;

					Output->push_back(dataptsession);

					Controle = true;

					return Output;
				}

			}


		}


		return Output;


	}
	

	vector<DataControle>* ControleDirectoryAsynchro::ControleLogInAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, std::string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControle>* Output=NULL;

		if(ControleGetLenght(args, Message,2))
		{ 
		if (ControleDirectoryUnwrap(args,Message,10) == true)
		{
			Output = new vector<DataControle>();

			DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

			DataControle dataptdirectory;

			dataptdirectory.Output.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

			Output->push_back(dataptdirectory);

			if(ControleUserUnwrap(args,Message,0)== true)
			{ 
				UserwrapAsynchro* PtUserWrap = ObjectWrap::Unwrap<UserwrapAsynchro>(args[0]->ToObject());

				DataControle dataptuser;

				dataptuser.Output.PtUserwrapAsynchro = PtUserWrap;

				Output->push_back(dataptuser);

				Controle = true;

				return Output;
			}
		
		}
		

		}

			
			return Output;


	}



	vector<DataControle>* ControleDirectoryAsynchro::ControleGetGroups(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, std::string& Message)
	{

		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControle>* Output=NULL;

		if (ControleGetLenght(args, Message, 1))
		{
			if (ControleDirectoryUnwrap(args, Message,10) == false)
			{

				return Output;

			}
			else
			{
				Output = new vector<DataControle>();

				DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

				DataControle dataptdirectory;

				dataptdirectory.Output.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

				Output->push_back(dataptdirectory);

				Controle = true;

				return Output;

			}


		}
		else
		{

			return Output;

		}

	}

	vector<DataControle>* ControleDirectoryAsynchro::ControleGetGroupwrapIDAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, std::string& Message)
	{
	
		return ControleGetGroups(args, Controle, Message);

	}

	vector<DataControle>* ControleDirectoryAsynchro::ControleGetGroupwrapNamesAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		return ControleGetGroups(args, Controle, Message);
	}

	vector<DataControle>* ControleDirectoryAsynchro::ControleGetGroupwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{

		vector<DataControle>* Output = ControleGetGroupSession(args, Controle, Message);

		if (Controle == true)
		{

			DataControle ddatapassage = Output->at(1);

			DataControle dataIdGroup;

			dataIdGroup.Output.GroupId = ddatapassage.Output.DataPassage;

			Output->pop_back();

			Output->push_back(dataIdGroup);

			return Output;
		}

		return Output;


	}

	vector<DataControle>* ControleDirectoryAsynchro::ControleGetGroupSession(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{

		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControle>* Output=NULL;

		if (ControleGetLenght(args, Message, 2))
		{
			if (ControleDirectoryUnwrap(args, Message,10) == true)
			{

				if (Controlestring(args, Message, 0) == true)
				{
					Output = new vector<DataControle>();

					DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

					DataControle dataptdirectory;

					dataptdirectory.Output.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

					Output->push_back(dataptdirectory);
				
					Utility util;

					string dataId = util.V8Utf8ValueToStdString(args[0]);

					DataControle ddatapassage;

					ddatapassage.Output.DataPassage = new char[dataId.length() + 1];;

					std::strcpy(ddatapassage.Output.DataPassage, dataId.c_str());

					Output->push_back(ddatapassage);

					Controle = true;
					
					return Output;

				}

			}
		
		}


			return Output;


	}
	
	vector<DataControle>*	ControleDirectoryAsynchro::ControleUserwrapBelongToAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message, int& MethodeNumber)
	{

		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControle>* Output = NULL;

		if (ControleGetLenght(args, Message, 3))
		{
			if (ControleDirectoryUnwrap(args, Message,10) == true)
			{
				Output = new vector<DataControle>();

				DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

				DataControle dataptdirectory;

				dataptdirectory.Output.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

				Output->push_back(dataptdirectory);

				if (ControleUserUnwrap(args, Message, 0) == true)
				{
					UserwrapAsynchro* PtUserwrapAsynchro = ObjectWrap::Unwrap<UserwrapAsynchro>(args[0]->ToObject());

					DataControle dataptuser;

					dataptuser.Output.PtUserwrapAsynchro = PtUserwrapAsynchro;

					Output->push_back(dataptuser);

					if (Controlestring(args, Message, 1) == true)
					{
						Utility util;

						string GroupId = util.V8Utf8ValueToStdString(args[1]);

						DataControle dataGroupId;

						dataGroupId.Output.GroupId = new char[GroupId.length() + 1];;

						std::strcpy(dataGroupId.Output.GroupId, GroupId.c_str());

						Output->push_back(dataGroupId);
						
						MethodeNumber = 1;

						Controle = true;

						return Output;

					}
					if (ControleGroupUnwrap(args, Message, 1) == true)
					{

						GroupwrapAsynchro* PtGroupwrapAsynchro = ObjectWrap::Unwrap<GroupwrapAsynchro>(args[1]->ToObject());

						DataControle dataptgroup;

						dataptgroup.Output.PtGroupwrapAsynchro = PtGroupwrapAsynchro;

						Output->push_back(dataptgroup);

						MethodeNumber = 2;

						Controle = true;

						return Output;

					}
				}
				if (ControleSessionUnwrap(args, Message, 0) == true)
				{
					if (Controlestring(args, Message, 1) == true)
					{
						SessionwrapAsynchro* PtSessionwrapAsynchro = ObjectWrap::Unwrap<SessionwrapAsynchro>(args[0]->ToObject());

						DataControle dataptSession;

						dataptSession.Output.PtSessionwrapAsynchro = PtSessionwrapAsynchro;

						Output->push_back(dataptSession);

						Utility util;

						string GroupId = util.V8Utf8ValueToStdString(args[1]);

						DataControle dataGroupId;

						dataGroupId.Output.GroupId = new char[GroupId.length() + 1];;

						std::strcpy(dataGroupId.Output.GroupId, GroupId.c_str());

						Output->push_back(dataGroupId);


						MethodeNumber = 3;

						Controle = true;

						return Output;

					}

				}
			}
		}
		Message="Wrong argument";
		
		return Output;
	}

	

	vector<DataControle>* ControleDirectoryAsynchro::ControleGetSessionwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
	
		vector<DataControle>* Output=ControleGetGroupSession(args, Controle, Message);

		if (Controle == true)
		{

			DataControle ddatapassage = Output->at(1);

			DataControle dataIdSession;

			dataIdSession.Output.SessionId = ddatapassage.Output.DataPassage;

			Output->pop_back();

			Output->push_back(dataIdSession);

			return Output;
		}

		return Output;
	
	}


	vector<DataControle>* ControleDirectoryAsynchro::ControleGetUserwrapAsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{

		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControle>* Output=NULL;

		if (ControleGetLenght(args, Message, 3))
		{
			if (ControleDirectoryUnwrap(args, Message,10) == true)
			{

				if (Controlestring(args, Message, 0) == true)
				{
					if (Controlestring(args, Message, 1) == true)
					{
						Output = new vector<DataControle>();

						DirectorywrapAsynchro* PtDirectorywrapAsynchro = ObjectWrap::Unwrap<DirectorywrapAsynchro>(args.Holder());

						DataControle dataptdirectory;

						dataptdirectory.Output.PtDirectorywrapAsynchro = PtDirectorywrapAsynchro;

						Output->push_back(dataptdirectory);

						Utility util;

						string UserId = util.V8Utf8ValueToStdString(args[0]);

						DataControle dataUserId;

						dataUserId.Output.UserId = new char[UserId.length() + 1];;

						std::strcpy(dataUserId.Output.UserId, UserId.c_str());

						Output->push_back(dataUserId);

						string PasswordId = util.V8Utf8ValueToStdString(args[1]);

						DataControle dataPasswordId;

						dataPasswordId.Output.Password = new char[PasswordId.length() + 1];;

						std::strcpy(dataPasswordId.Output.Password, PasswordId.c_str());

						Output->push_back(dataPasswordId);


						Controle = true;

						return Output;
					}

				}

			}

		}


		return Output;


	}

}