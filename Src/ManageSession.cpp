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

		std::lock_guard<std::mutex> lockGuard(myMutex);

		for (auto const& Iterator : list){
		
			if (Iterator.IdUser == IdUser)

			{
				return Iterator.cookies;
			}
		}

		return "";

	}

	string ManageSession::GetUserId(string cookies)
	{
		std::lock_guard<std::mutex> lockGuard(myMutex);

		for (auto const& Iterator : list){
		
			if (Iterator.cookies == cookies)
			{

				return Iterator.IdUser;
			}
		
		}

		return "";

	}
	void ManageSession::Register(string IdUser, string cookies, string Username, double InputTtl)
	{
		
		std::lock_guard<std::mutex> lockGuard(myMutex);

		UnionUserSession Newelement;
		
		Newelement.cookies = cookies;
		
		Newelement.IdUser = IdUser;

		Newelement.Username = Username;

		(Newelement.MaxAgeTtl) = InputTtl;

		time_t OperationTime = time(0);

		SaveOperation(OperationTime, "Login", Newelement.getWASID(), Newelement.IdUser, Newelement.Username);

		this->list.push_back(Newelement);

	}

	bool ManageSession::FindByUserId(string IdUser)
	{
		std::lock_guard<std::mutex> lockGuard(myMutex);

		for (auto const& Iterator : list){
		
			if (Iterator.IdUser == IdUser)
			{

				return true;
			}

		}

		return false;
	}

	bool ManageSession::findcookiesbywsid(string& wsid)
	{
		std::lock_guard<std::mutex> lockGuard(myMutex);

		for (auto Iterator : list){
		
			if (Iterator.getWASID() == wsid)
			{
				wsid = Iterator.cookies;

				return true;
			}
		
		}
		
	
		
		return false;
	}
	vector<UnionUserSession> ManageSession::getList()
	{
		vector < UnionUserSession > Output;
		
		std::lock_guard<std::mutex> lockGuard(myMutex);

		for (auto Iterator : list){

			Iterator.cookies = Iterator.getWASID();

			Output.push_back(Iterator);
		}
		
		return Output;
	}
	void ManageSession::Remove(string IdUser)
	{
		std::lock_guard<std::mutex> lockGuard(myMutex);


		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list[Iterator];

			if (Newelement.IdUser == IdUser){ 
				
				time_t OperationTime = time(0);

				SaveOperation(OperationTime, "Logout", Newelement.getWASID(), Newelement.IdUser, Newelement.Username);

				
				
				list.erase(list.begin() + Iterator); 
			
				
			}

		}

	}
	void ManageSession::RemoveBycookies(string cookies)
	{

		std::lock_guard<std::mutex> lockGuard(myMutex);

		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			UnionUserSession Newelement = list[Iterator];

			if (Newelement.cookies == cookies){
				
				time_t OperationTime = time(0);

				SaveOperation(OperationTime, "Logout", Newelement.getWASID(), Newelement.IdUser, Newelement.Username);
			
				list.erase(list.begin() + Iterator);

			}

		}

	}

	void ManageSession::UpdateBycookies(string cookies, double InputTtl)
	{
		
		std::lock_guard<std::mutex> lockGuard(myMutex);

		for (int Iterator = 0; Iterator < list.size(); Iterator++)
		{
			

			if (list[Iterator].cookies == cookies){

				time_t OperationTime = time(0);

				SaveOperation(OperationTime, "Update", list[Iterator].getWASID(), list[Iterator].IdUser, list[Iterator].Username);

				(list[Iterator].MaxAgeTtl) = InputTtl;

			}

		}

		
	}
	void ManageSession::Affiche()
	{

		if (list.size()>0)
		{ 
			std::lock_guard<std::mutex> lockGuard(myMutex);

			for (auto  Iterator : list){

				std::cout << "Username :" << Iterator.Username << "  IdUser :" << Iterator.IdUser << " WSID :" << Iterator.getWASID() << " TTl : " << Iterator.MaxAgeTtl << endl;

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

	void ManageSession::Task(int TimeSleep, IDirectory *Pt_Directory, vector<UnionUserSession>  & list1)
	{

		while (true)
		{
		
		std::chrono::milliseconds duration(TimeSleep);

	    std:this_thread::sleep_for(duration);

		int Nombre = list1.size();

		int time1 = TimeSleep / 1000;

			if (Nombre > 0)
			{
				std::lock_guard<std::mutex> lockGuard(myMutex);

				for (int Iterator = 0; Iterator < Nombre; Iterator++)
				{
					list1.at(Iterator);

					if (list1[Iterator].MaxAgeTtl - time1 <= 0){

						ISession* inSession = new Session(list1[Iterator].cookies);

						Pt_Directory->LogOut(inSession);

						delete inSession;

						time_t OperationTime = time(0);


						SaveOperation(OperationTime, "Logout", list1[Iterator].getWASID(), list1[Iterator].IdUser, list1[Iterator].Username);


						list1.erase(list1.begin() + Iterator);


						if (Iterator == 0)
						{
		
						}
						else if (Iterator != 0)
						{
							Iterator--;
						}

						Nombre = Nombre - 1;
					}
					else
					{

						list1[Iterator].MaxAgeTtl = list1[Iterator].MaxAgeTtl - time1;


					}

				}
			}
			

	}
	
	}


}







