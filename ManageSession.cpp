#include "ManageSession.h"
#include<string>
#include<iostream>
using namespace std;
namespace WaDirectory_Data
{
	ManageSession::ManageSession()
	{
		this->list = new vector < UnionUserSession >() ;
	}


	ManageSession::~ManageSession()
	{
	}

	string ManageSession::Getcookies(string IdUser)
	{
		for (int Iterator = 0; Iterator < list->size(); Iterator++)
		{
			UnionUserSession Newelement = list->at(Iterator);

			if (Newelement.IdUser == IdUser)return Newelement.cookies;

		}
		return "";

	}
	void ManageSession::Register(string IdUser, string cookies,string Username)
	{
		UnionUserSession Newelement;
		
		Newelement.cookies = cookies;
		
		Newelement.IdUser = IdUser;

		Newelement.Username = Username;

		this->list->push_back(Newelement);
	}

	bool ManageSession::FindByUserId(string IdUser)
	{
		for (int Iterator = 0; Iterator < list->size(); Iterator++)
		{
			UnionUserSession Newelement = list->at(Iterator);

			if(Newelement.IdUser==IdUser)return true;

		}
		return false;
	}
	vector<UnionUserSession> ManageSession::getList()
	{
		vector < UnionUserSession > Output;
		
		for (int Iterator = 0; Iterator < list->size(); Iterator++)
		{
			UnionUserSession Newelement = list->at(Iterator);

			Newelement.cookies = Newelement.getWASID();

			Output.push_back(Newelement);
		}
		return Output;
	}
	void ManageSession::Remove(string IdUser)
	{
		for (int Iterator = 0; Iterator < list->size(); Iterator++)
		{
			UnionUserSession Newelement = list->at(Iterator);

			if (Newelement.IdUser == IdUser)list->erase(list->begin()+Iterator);

		}

	}
	void ManageSession::RemoveBycookies(string cookies)
	{
		for (int Iterator = 0; Iterator < list->size(); Iterator++)
		{
			UnionUserSession Newelement = list->at(Iterator);

			if (Newelement.cookies == cookies)list->erase(list->begin() + Iterator);

		}

	}
	void ManageSession::Affiche()
	{
		vector<UnionUserSession> List = getList();
		std::cout << "Entrer Affiche" << endl;

		for (int Iterator = 0; Iterator < List.size(); Iterator++)
		{
			UnionUserSession Newelement = List.at(Iterator);

			std::cout << "Username :" + Newelement.Username + "  IdUser :" + Newelement.IdUser + " WSID :" + Newelement.cookies << endl;

		}
	
	}


}







