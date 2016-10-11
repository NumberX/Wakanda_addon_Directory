#include"ControleDirectorysynchro.h"
#include"Directorywrap.h"
#include"ControleBasesynchro.h"
#include"DataControlesyn.h"
#include"Utility.h"
#include <node.h>
#include <node_object_wrap.h>
#include<iostream>
#include<regex>
using namespace WaDirectory_View;
namespace WaDirectory_Controle{
	ControleDirectorysynchro::ControleDirectorysynchro(){
	
	}
	ControleDirectorysynchro::~ControleDirectorysynchro(){
	
	
	}

	bool ControleDirectorysynchro::valide(string Phrase)
	{

		std::regex word_regex("\\w+");
		if (std::regex_match(Phrase, word_regex)) {


			return true;
		}

		return false;


	}

	vector<DataControlesyn>* ControleDirectorysynchro::ControleLogOutsynchro1(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, std::string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControlesyn>* Output=NULL;

		
			if (ControleDirectoryUnwrap(args, Message, 10) == true)
			{
				Directorywrap* PtDirectorywrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

				if (ControleValideDirectoryData(PtDirectorywrap->GetDirectory(), Message))
				{
					if (ControleGetLenght(args, Message, 1))
					{
				
						Output = new vector<DataControlesyn>();

						DataControlesyn dataptdirectory;

						dataptdirectory.Output.PtDirectorywrap = PtDirectorywrap;

						Output->push_back(dataptdirectory);

							if (ControleSessionUnwrap(args, Message, 0) == true)
							{
						
								Sessionwrap* PtSessionWrap = ObjectWrap::Unwrap<Sessionwrap>(args[0]->ToObject());

								DataControlesyn dataptsession;

								dataptsession.Output.PtSessionwrap = PtSessionWrap;

								Output->push_back(dataptsession);

								Controle = true;

								return Output;
							}

					}

					if (ControleGetLenght(args, Message, 0))
					{

						Output = new vector<DataControlesyn>();

						DataControlesyn dataptdirectory;

						dataptdirectory.Output.PtDirectorywrap = PtDirectorywrap;

						Output->push_back(dataptdirectory);
						
						Local<Context> CurentContext = isolate->GetCurrentContext();

						DataControlesyn dataPtSession;

						Local<Value> SessionObject1 = CurentContext->GetEmbedderData(0);

						Local<Object> SessionObject = SessionObject1->ToObject();

						Sessionwrap* PtSession = Sessionwrap::Unwrap<Sessionwrap>(SessionObject);

						dataPtSession.Output.PtSessionwrap = PtSession;

						Output->push_back(dataPtSession);

						

						Controle = true;

						return Output;
						

					}
				}


			}


		return Output;


	}
	

	vector<DataControlesyn>* ControleDirectorysynchro::ControleLogInsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, std::string& Message)
	{
		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControlesyn>* Output=NULL;

		if(ControleGetLenght(args, Message,2))
		{ 
		if (ControleDirectoryUnwrap(args,Message,10) == true)
		{
			

			Directorywrap* PtDirectorywrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

			if (ControleValideDirectoryData(PtDirectorywrap->GetDirectory(), Message))
			{
				Output = new vector<DataControlesyn>();

				DataControlesyn dataptdirectory;

				dataptdirectory.Output.PtDirectorywrap = PtDirectorywrap;

				Output->push_back(dataptdirectory);

				if (ControleUserUnwrap(args, Message, 0) == true)
				{
					Userwrap* PtUserWrap = ObjectWrap::Unwrap<Userwrap>(args[0]->ToObject());

					DataControlesyn dataptuser;

					dataptuser.Output.PtUserwrap = PtUserWrap;

					Output->push_back(dataptuser);

					Controle = true;

					return Output;
				}
			}
		
		}
		

		}

			
			return Output;


	}



	vector<DataControlesyn>* ControleDirectorysynchro::ControleGetGroupssynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, std::string& Message)
	{

		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControlesyn>* Output=NULL;

		if (ControleGetLenght(args, Message, 0))
		{
			if (ControleDirectoryUnwrap(args, Message,10) == false)
			{

				return Output;

			}
			else
			{
				Directorywrap* PtDirectorywrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

				if (ControleValideDirectoryData(PtDirectorywrap->GetDirectory(), Message))
				{ 
				Output = new vector<DataControlesyn>();

				DataControlesyn dataptdirectory;

				dataptdirectory.Output.PtDirectorywrap = PtDirectorywrap;

				Output->push_back(dataptdirectory);

				Controle = true;

				
				return Output;
				}

			}


		}


			return Output;

		

	}

	vector<DataControlesyn>* ControleDirectorysynchro::ControleGetGroupwrapIDsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, std::string& Message)
	{
	
		return ControleGetGroupssynchro(args, Controle, Message);

	}

	vector<DataControlesyn>* ControleDirectorysynchro::ControleGetGroupwrapNamessynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{
		return ControleGetGroupssynchro(args, Controle, Message);
	}

	vector<DataControlesyn>* ControleDirectorysynchro::ControleGetUserwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{

		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControlesyn>* Output = NULL;



		if (ControleGetLenght(args, Message, 2))
		{
			if (ControleDirectoryUnwrap(args, Message, 10) == true)
			{
				
				if (Controlestring(args, Message, 0) == true)
				{

					if (Controlestring(args, Message, 1) == true)
					{
						Directorywrap* PtDirectorywrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

						
						if (ControleValideDirectoryData(PtDirectorywrap->GetDirectory(), Message))
						{

							Tools::Utility util;

							string UserId = util.V8Utf8ValueToStdString(args[0]);

							string PasswordId = util.V8Utf8ValueToStdString(args[1]);
							if (valide(PasswordId) && (valide(UserId))){

							Output = new vector<DataControlesyn>();

							DataControlesyn dataptdirectory;

							dataptdirectory.Output.PtDirectorywrap = PtDirectorywrap;

							Output->push_back(dataptdirectory);

							DataControlesyn dataUserId;

							dataUserId.Output.UserId = new char[UserId.length() + 1];;

							std::strcpy(dataUserId.Output.UserId, UserId.c_str());

							Output->push_back(dataUserId);

							DataControlesyn dataPasswordId;

							dataPasswordId.Output.Password = new char[PasswordId.length() + 1];;

							std::strcpy(dataPasswordId.Output.Password, PasswordId.c_str());

							Output->push_back(dataPasswordId);

							string Username1 = UserId;

							string Password1 = PasswordId;


							
								Controle = true;
							}

							

							return Output;
						}
					}

				}

			}

		}

		return Output;


	}

	vector<DataControlesyn>* ControleDirectorysynchro::ControleGetGroupSessionsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{

		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControlesyn>* Output=NULL;

		if (ControleGetLenght(args, Message, 1))
		{
			if (ControleDirectoryUnwrap(args, Message,10) == true)
			{

				if (Controlestring(args, Message, 0) == true)
				{
					Directorywrap* PtDirectorywrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

					if (ControleValideDirectoryData(PtDirectorywrap->GetDirectory(), Message))
					{

						Output = new vector<DataControlesyn>();

						DataControlesyn dataptdirectory;

						dataptdirectory.Output.PtDirectorywrap = PtDirectorywrap;

						Output->push_back(dataptdirectory);

						Tools::Utility util;

						string dataId = util.V8Utf8ValueToStdString(args[0]);

						DataControlesyn ddatapassage;

						ddatapassage.Output.DataPassage = new char[dataId.length() + 1];;

						std::strcpy(ddatapassage.Output.DataPassage, dataId.c_str());

						Output->push_back(ddatapassage);

						Controle = true;

						return Output;
					}

				}

			}
		
		}


			return Output;


	}
	bool ControleDirectorysynchro::ControleValideDirectoryData(IDirectory *PtDirectory,string& Message)
	{
		if (PtDirectory == NULL)
		{
			Message = "IDirectory is Null";
			return false;
		}
		return true;

	}
	vector<DataControlesyn>*	ControleDirectorysynchro::ControleUserwrapBelongTosynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message, int& MethodeNumber)
	{

		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControlesyn>* Output = NULL;
	
		if (ControleDirectoryUnwrap(args, Message, 10) == true)
		{
			Directorywrap* PtDirectorywrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

			if (ControleValideDirectoryData(PtDirectorywrap->GetDirectory(), Message))
			{

				DataControlesyn dataptdirectory;

				dataptdirectory.Output.PtDirectorywrap = PtDirectorywrap;

				if (ControleGetLenght(args, Message, 3))
				{
			    Output = new vector<DataControlesyn>();

				Output->push_back(dataptdirectory);

				if (ControleUserUnwrap(args, Message, 0) == true)
				{
					Userwrap* PtUserwrap = ObjectWrap::Unwrap<Userwrap>(args[0]->ToObject());

					DataControlesyn dataptuser;

					dataptuser.Output.PtUserwrap = PtUserwrap;

					Output->push_back(dataptuser);

					if (Controlestring(args, Message, 1) == true)
					{
						Tools::Utility util;

						string GroupId = util.V8Utf8ValueToStdString(args[1]);

						DataControlesyn dataGroupId;

						dataGroupId.Output.GroupId = new char[GroupId.length() + 1];;

						std::strcpy(dataGroupId.Output.GroupId, GroupId.c_str());

						Output->push_back(dataGroupId);
						
						MethodeNumber = 1;

						Controle = true;

						return Output;

					}
					if (ControleGroupUnwrap(args, Message, 1) == true)
					{

						Userwrap* PtPtUserwrap = ObjectWrap::Unwrap<Userwrap>(args[1]->ToObject());

						DataControlesyn dataptgroup;

						dataptgroup.Output.PtUserwrap = PtPtUserwrap;

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
						Sessionwrap* PtSessionwrap = ObjectWrap::Unwrap<Sessionwrap>(args[0]->ToObject());

						DataControlesyn dataptSession;

						dataptSession.Output.PtSessionwrap = PtSessionwrap;

						Output->push_back(dataptSession);

						Tools::Utility util;

						string GroupId = util.V8Utf8ValueToStdString(args[1]);

						DataControlesyn dataGroupId;

						dataGroupId.Output.GroupId = new char[GroupId.length() + 1];;

						std::strcpy(dataGroupId.Output.GroupId, GroupId.c_str());

						Output->push_back(dataGroupId);


						MethodeNumber = 3;

						Controle = true;

						return Output;

					}

				}
				}
				if (ControleGetLenght(args, Message, 2))
				{
					Output = new vector<DataControlesyn>();

					Output->push_back(dataptdirectory);

					Local<Context> CurentContext = isolate->GetCurrentContext();

					MethodeNumber = 4;

					DataControlesyn dataPtSession;

					Local<Value> SessionObject1 = CurentContext->GetEmbedderData(0);

					Local<Object> SessionObject = SessionObject1->ToObject();

					Sessionwrap* PtSession = Sessionwrap::Unwrap<Sessionwrap>(SessionObject);

					dataPtSession.Output.PtSessionwrap = PtSession;

					Output->push_back(dataPtSession);

					Controle = true;
					
					return Output;


				}
			}
		}
		Message="Wrong argument";
		
		return Output;
	}

	
	vector<DataControlesyn>* ControleDirectorysynchro::ControleGetGroupwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message)
	{

		vector<DataControlesyn>* Output = ControleGetGroupSessionsynchro(args, Controle, Message);

		if (Controle == true)
		{

			DataControlesyn ddatapassage = Output->at(1);

			DataControlesyn dataIdGroup;

			dataIdGroup.Output.GroupId = ddatapassage.Output.DataPassage;

			Output->pop_back();

			Output->push_back(dataIdGroup);

			return Output;
		}

		return Output;


	}

	vector<DataControlesyn>* ControleDirectorysynchro::ControleGetSessionwrapsynchro(const v8::FunctionCallbackInfo<v8::Value>& args, bool& Controle, string& Message,int& Methode)
	{
	
		Isolate* isolate = args.GetIsolate();

		Controle = false;

		vector<DataControlesyn>* Output = NULL;

		if (ControleDirectoryUnwrap(args, Message, 10) == true)
		{
			Directorywrap* PtDirectorywrap = ObjectWrap::Unwrap<Directorywrap>(args.Holder());

			DataControlesyn dataptdirectory;

			dataptdirectory.Output.PtDirectorywrap = PtDirectorywrap;
			if (ControleValideDirectoryData(PtDirectorywrap->GetDirectory(), Message))
			{


				if (ControleGetLenght(args, Message, 2))

				{


					if (Controlestring(args, Message, 0) == true)
					{


						Methode = 1;

						Output = new vector<DataControlesyn>();

						Output->push_back(dataptdirectory);

						Tools::Utility util;

						string dataId = util.V8Utf8ValueToStdString(args[0]);

						DataControlesyn dataIdSession;

						dataIdSession.Output.SessionId = new char[dataId.length() + 1];;

						std::strcpy(dataIdSession.Output.SessionId, dataId.c_str());

						Output->push_back(dataIdSession);

						Controle = true;

						return Output;
					}
				}
				if (ControleGetLenght(args, Message, 1))

				{

					Local<Context> CurentContext = isolate->GetCurrentContext();

					Methode = 2;

					Output = new vector<DataControlesyn>();

					Output->push_back(dataptdirectory);

					DataControlesyn dataPtSession;

					Local<Value> SessionObject1 = CurentContext->GetEmbedderData(0);

					Local<Object> SessionObject = SessionObject1->ToObject();

					Sessionwrap* PtSession = Sessionwrap::Unwrap<Sessionwrap>(SessionObject);

					dataPtSession.Output.PtSessionwrap = PtSession;

					Output->push_back(dataPtSession);

					Controle = true;

					return Output;
					
				

				}

			}

		}


		return Output;

	
	}


}
