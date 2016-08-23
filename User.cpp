#include "User.h"
#include"Session.h"
#include"Group.h"
#include"Directory.h"
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
	void User::Set_Directory(Directory* Pt_Directory)
	{
	
		this->Pt_Directory = Pt_Directory;
	}

	User::~User()
	{
	}


	Directory* User::GetDirectory() const
	{
		return this->Pt_Directory;
	}


	void User::GetName(string& outName)
	{
		XMLparser PtparseurXml(this->Pt_Directory->Get_Url_Directory());

		outName = PtparseurXml.NameUserById(this->Id, "name");
	
	}


	bool User::BelongsToGroup(const string& inGroupName)
	{
		bool resultat=false;

		Jsonparser Jspar(this->GetDirectory()->Get_Url_Wakanda(), this->GetDirectory()->Get_Url_Wakanda());
		
		string wsid = Jspar.login(this->Username, this->Password);
		
		if (wsid.length() > 0)
		{
			
		
			resultat=Jspar.currentUserBelongsTo("", inGroupName);
			
			
		}
		return resultat;
	}


	bool User::BelongsToGroup(const Group* inGroupName)
	{

		bool resultat = false;

		Jsonparser Jspar(this->GetDirectory()->Get_Url_Wakanda(), this->GetDirectory()->Get_Url_Wakanda());
		
		string wsid = Jspar.login(this->Username, this->Password);
		
		if (wsid.length() > 0)
		{

			resultat = Jspar.currentUserBelongsTo("", inGroupName->Namegroup);
			
		}
		return resultat;
	}


	bool User::IsLoggedIn(const Session* inSession)
	{


		bool resultat = false;
		
		Jsonparser Jspar(this->GetDirectory()->Get_Url_Wakanda(), this->GetDirectory()->Get_Url_Wakanda()); 
		
		Jspar.cookie = inSession->cookies;
		
		vector<string> v1= Jspar.currentuser();
		
		if (v1[0] == this->Username)
		{
			
			return true;
		}

			
		
			return resultat;
		
		
	}
}