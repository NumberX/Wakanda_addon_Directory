#include "ManageSession.h"
#include"IDirectory.h"
#include"ISession.h"
#include"Session.h"
#include<string>
#include<iostream>
#include<thread>
#include <chrono>
#include <fstream>
#include <ctime>
using namespace std;
namespace WaDirectory_Data
{
	ManageSession::ManageSession()
	{
		
	}


	ManageSession::~ManageSession()
	{
	}

	string ManageSession::Getcookies(string IdUser)
	{
		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			if (Newelement.IdUser == IdUser)return Newelement.cookies;

		}
		return "";

	}

	string ManageSession::GetUserId(string cookies)
	{
		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			if (Newelement.cookies ==cookies)return Newelement.IdUser;

		}
		return "";

	}
	void ManageSession::Register(string IdUser, string cookies, string Username, double InputTtl)
	{
		UnionUserSession Newelement;
		
		Newelement.cookies = cookies;
		
		Newelement.IdUser = IdUser;

		Newelement.Username = Username;

		Newelement.MaxAgeTtl = InputTtl;

		time_t OperationTime = time(0);

		SaveOperation(OperationTime, "Login", Newelement.getWASID(), Newelement.IdUser, Newelement.Username);

		this->list.push_back(Newelement);
	}

	bool ManageSession::FindByUserId(string IdUser)
	{
		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			if(Newelement.IdUser==IdUser)return true;

		}
		return false;
	}

	bool ManageSession::findcookiesbywsid(string& wsid)
	{
		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			if (Newelement.getWASID() == wsid)
			{ 
				wsid = Newelement.cookies;
				return true;
			}
		}
		return false;
	}
	vector<UnionUserSession> ManageSession::getList()
	{
		vector < UnionUserSession > Output;
		
		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			Newelement.cookies = Newelement.getWASID();

			Output.push_back(Newelement);
		}
		return Output;
	}
	void ManageSession::Remove(string IdUser)
	{
		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			if (Newelement.IdUser == IdUser){ 
				
				time_t OperationTime = time(0);

				SaveOperation(OperationTime, "Logout", Newelement.getWASID(), Newelement.IdUser, Newelement.Username);

				
				list.erase(list.begin() + Iterator); }

		}

	}
	void ManageSession::RemoveBycookies(string cookies)
	{
		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			if (Newelement.cookies == cookies){
				

				time_t OperationTime = time(0);

				SaveOperation(OperationTime, "Logout", Newelement.getWASID(), Newelement.IdUser, Newelement.Username);
			
				list.erase(list.begin() + Iterator);
			
			}

		}

	}

	void ManageSession::UpdateBycookies(string cookies, double InputTtl)
	{
		
		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			

			if (list.at(Iterator).cookies == cookies){

				time_t OperationTime = time(0);

				SaveOperation(OperationTime, "Update", list.at(Iterator).getWASID(), list.at(Iterator).IdUser, list.at(Iterator).Username);
			
				list.at(Iterator).MaxAgeTtl = InputTtl;
			}

		}
		
	}
	void ManageSession::Affiche()
	{
		//vector<UnionUserSession> List = getList();
		std::cout << "Entrer Affiche :" +list.size()<< endl;
		if (list.size()>0)
		{ 
		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			std::cout << "Username :" << Newelement.Username << "  IdUser :" << Newelement.IdUser << " WSID :" << Newelement.getWASID() << " TTl : " << Newelement.MaxAgeTtl<< endl;

		}
		}
	
	}

	void ManageSession::SaveOperation(time_t OperationTime, string TypeOperation, string wsid, string IdUser, string NameUser)
	{

		struct tm * now = localtime(&OperationTime);

		ofstream outputFile("SessionManager.log", ios::out | ios::app);

		outputFile << (now->tm_year + 1900) << "-" << (now->tm_mon + 1) << "-" << now->tm_mday << "-" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "|" << TypeOperation << "|" << wsid << "|" << IdUser << "|" << NameUser << endl;

		outputFile.close();
	}

	void ManageSession::Task(int TimeSleep,IDirectory *Pt_Directory,vector<UnionUserSession>  & list1)
	{

		std::chrono::milliseconds duration(TimeSleep);

	
		std:this_thread::sleep_for(duration);

		int Nombre=list1.size();
		
		int time1 = TimeSleep / 1000;

		if (Nombre>0)
		{ 
		for (int Iterator = 0; Iterator < Nombre; Iterator++)
		{
			list1.at(Iterator);

			if (list1.at(Iterator).MaxAgeTtl - time1 <= 0){

				ISession* inSession = new Session(list1.at(Iterator).cookies);

				Pt_Directory->LogOut(inSession);

				time_t OperationTime = time(0);

				SaveOperation(OperationTime, "Logout", list1.at(Iterator).getWASID(), list1.at(Iterator).IdUser, list1.at(Iterator).Username);

				list1.erase(list1.begin() + Iterator);
				
				if ((Iterator != 0) || (Iterator == 0))
				{
					Iterator--;
				}

				Nombre=Nombre-1;
			}
			else
			{
				list1.at(Iterator).MaxAgeTtl = list1.at(Iterator).MaxAgeTtl - time1;
			}

		}
		}
		//this->Affiche();

	
	try
	{
		// instructions pouvant déclencher des exceptions 
		// dérivant de std::exception 
		this->Task(TimeSleep, Pt_Directory,list1);
	
	}
	catch (const std::exception & e)
	{
		std::cerr <<"Ereur from task"<<e.what();
	}
	
	}


}







