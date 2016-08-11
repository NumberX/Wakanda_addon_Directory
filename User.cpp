#include "User.h"
#include"Session.h"
#include"Group.h"
#include"Jsonparser.h"
#include"XMLparser.h"
#include<string>
#include<iostream>
using namespace std;
using namespace  WaDirectory_data;

namespace WaDirectory
{


	User::User()
	{
	}
	User::User(string Username,string FullName,string Id,string Password)
	{
		this->Username = Username;
		this->FullName = FullName;
		this->Id = Id;
		this->Password = Password;
	}

	User::~User()
	{
	}


	Directory* User::GetDirectory() const
	{
		return nullptr;
	}


	void User::GetName(string& outName)
	{
		XMLparser parse;

		outName = parse.NameUserById(this->Id, "name");
	
	}


	bool User::BelongsToGroup(const string& inGroupName)
	{
		bool resultat=false;// = new Session();
		Jsonparser Jspar;
		string wsid = Jspar.login(this->Username, this->Password);
		if (wsid.length() > 0)
		{
			
			resultat=Jspar.currentUserBelongsTo("", inGroupName);
			return resultat;
		}
		return resultat;
	}


	bool User::BelongsToGroup(const Group* inGroupName)
	{

		bool resultat = false;// = new Session();
		Jsonparser Jspar;
		string wsid = Jspar.login(this->Username, this->Password);
		if (wsid.length() > 0)
		{

			resultat = Jspar.currentUserBelongsTo("", inGroupName->Namegroup);
			
			return resultat;
		}
		return resultat;
	}


	bool User::IsLoggedIn(const Session* inSession)
	{


		bool resultat = false;
		Jsonparser Jspar;
		Jspar.cookie=inSession->cookies;
		vector<string> v1= Jspar.currentuser();
		if (v1[0] == this->Username)
		{
			
			return true;
		}

			
		
			return resultat;
		
		
	}
}