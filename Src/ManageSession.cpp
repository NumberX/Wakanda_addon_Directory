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
#include<mutex>
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

		myMutex.lock();
		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			if (Newelement.IdUser == IdUser)

			{
				myMutex.unlock();
				return Newelement.cookies;
			}
		}
		
		myMutex.unlock();

		return "";

	}

	string ManageSession::GetUserId(string cookies)
	{
		myMutex.lock();


		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			if (Newelement.cookies == cookies)
			{
				myMutex.unlock();

				return Newelement.IdUser;
			}
		}

		myMutex.unlock();
		return "";

	}
	void ManageSession::Register(string IdUser, string cookies, string Username, double InputTtl)
	{
		
		myMutex.lock();

		UnionUserSession Newelement;
		
		Newelement.cookies = cookies;
		
		Newelement.IdUser = IdUser;

		Newelement.Username = Username;

		std::cout << "\n \n TTl Register \n \n" << InputTtl << endl;

		(Newelement.MaxAgeTtl) = InputTtl;

		time_t OperationTime = time(0);

		SaveOperation(OperationTime, "Login", Newelement.getWASID(), Newelement.IdUser, Newelement.Username);

		this->list.push_back(Newelement);

		myMutex.unlock();
	}

	bool ManageSession::FindByUserId(string IdUser)
	{
		myMutex.lock();

		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			if (Newelement.IdUser == IdUser)
			{
				myMutex.unlock();

				return true;
			}
		}
		myMutex.unlock();

		return false;
	}

	bool ManageSession::findcookiesbywsid(string& wsid)
	{
		myMutex.lock();

		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			if (Newelement.getWASID() == wsid)
			{ 
				wsid = Newelement.cookies;
		
				myMutex.unlock();
				
				return true;
			}
		}
		
		myMutex.unlock();
		
		return false;
	}
	vector<UnionUserSession> ManageSession::getList()
	{
		vector < UnionUserSession > Output;
		
		myMutex.lock();

		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			Newelement.cookies = Newelement.getWASID();

			Output.push_back(Newelement);
		}

		myMutex.unlock();
		
		return Output;
	}
	void ManageSession::Remove(string IdUser)
	{
		myMutex.lock();

		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			if (Newelement.IdUser == IdUser){ 
				
				time_t OperationTime = time(0);

				SaveOperation(OperationTime, "Logout", Newelement.getWASID(), Newelement.IdUser, Newelement.Username);

				
				
				list.erase(list.begin() + Iterator); 
			
				
			}

		}

		myMutex.unlock();

	}
	void ManageSession::RemoveBycookies(string cookies)
	{

		myMutex.lock();

		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			if (Newelement.cookies == cookies){
				

				time_t OperationTime = time(0);

				SaveOperation(OperationTime, "Logout", Newelement.getWASID(), Newelement.IdUser, Newelement.Username);
			
				list.erase(list.begin() + Iterator);

				
			
			}

		}
		myMutex.unlock();

	}

	void ManageSession::UpdateBycookies(string cookies, double InputTtl)
	{
		
		myMutex.lock();

		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			

			if (list.at(Iterator).cookies == cookies){

				time_t OperationTime = time(0);

				SaveOperation(OperationTime, "Update", list.at(Iterator).getWASID(), list.at(Iterator).IdUser, list.at(Iterator).Username);

				(list.at(Iterator).MaxAgeTtl) = InputTtl;

			}

		}

		myMutex.unlock();

		
	}
	void ManageSession::Affiche()
	{

		if (list.size()>0)
		{ 
			myMutex.lock();

		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list.at(Iterator);

			std::cout << "Username :" << Newelement.Username << "  IdUser :" << Newelement.IdUser << " WSID :" << Newelement.getWASID() << " TTl : " << Newelement.MaxAgeTtl<< endl;

		}

		myMutex.unlock();
		
		}
	
	}

	void ManageSession::SaveOperation(time_t OperationTime, string TypeOperation, string wsid, string IdUser, string NameUser)
	{

		struct tm * now = localtime(&OperationTime);

		ofstream outputFile("SessionManager.log", ios::out | ios::app);

		outputFile << (now->tm_year + 1900) << "-" << (now->tm_mon + 1) << "-" << now->tm_mday << "-" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "|" << TypeOperation << "|" << wsid << "|" << IdUser << "|" << NameUser << endl;

		outputFile.close();
	}

	void ManageSession::Task(int TimeSleep, IDirectory *Pt_Directory, vector<UnionUserSession>  & list1)
	{

		while (true)
		{
		Affiche();

		std::chrono::milliseconds duration(TimeSleep);

	    std:this_thread::sleep_for(duration);

		std::cout << "\n \n \n Begin \n \n \n " << endl;

		int Nombre = list1.size();

		int time1 = TimeSleep / 1000;

		if (Nombre > 0)
		{
			myMutex.lock();

			for (int Iterator = 0; Iterator < Nombre; Iterator++)
			{
				list1.at(Iterator);

				if (list1.at(Iterator).MaxAgeTtl - time1 <= 0){

					ISession* inSession = new Session(list1.at(Iterator).cookies);

					Pt_Directory->LogOut(inSession);

					delete inSession;

					time_t OperationTime = time(0);

					Affiche();

					SaveOperation(OperationTime, "Logout", list1.at(Iterator).getWASID(), list1.at(Iterator).IdUser, list1.at(Iterator).Username);

					list1.erase(list1.begin() + Iterator);


					if ((Iterator != 0) || (Iterator == 0))
					{
						Iterator--;
					}

					Nombre = Nombre - 1;
				}
				else
				{


					list1.at(Iterator).MaxAgeTtl = list1.at(Iterator).MaxAgeTtl - time1;


				}

			}

			myMutex.unlock();
		}
		std::cout << "\n \n \n End \n \n \n " << endl;

	};
	
	}


}







