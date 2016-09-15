#include "User.h"
#include"Session.h"
#include"Group.h"
#include"Directory.h"
#include"Jsonparser.h"
#include"XMLparser.h"
#include<string>
#include<iostream>
using namespace std;

namespace WaDirectory_Data
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
	void User::Set_Directory(IDirectory* Pt_Directory)
	{
	
		this->Pt_Directory = Pt_Directory;
	}

	User::~User()
	{
	}


	IDirectory* User::GetDirectory() 
	{
		return this->Pt_Directory;
	}


	void User::GetName(string& outName)
	{
		XMLparser PtparseurXml(this->Pt_Directory->Get_Url_Directory());

		outName = PtparseurXml.NameUserById(this->Id, "name");
		//outName = this->Username;
	
	}


	bool User::BelongsToGroup(const string& inGroupName)
	{
		bool resultat;

		Jsonparser *Jspar;
		Jspar=new Jsonparser(this->GetDirectory()->Get_Url_Wakanda(), this->GetDirectory()->Get_Url_Wakanda());
		
		string wsid = Jspar->login(this->Username, this->Password);
		
		Jspar->cookie = wsid;
		
		resultat = Jspar->currentUserBelongsTo(inGroupName, "");
		

		return resultat;
	}


	bool User::BelongsToGroup(const IGroup* inGroupName)
	{

		bool resultat = false;

		Jsonparser *Jspar;
		Jspar = new Jsonparser(this->GetDirectory()->Get_Url_Wakanda(), this->GetDirectory()->Get_Url_Wakanda());
		
		bool wsid = Jspar->isvalid(this->Username, this->Password);
		
		if (wsid==true)
		{

			string wsid = Jspar->login(this->Username, this->Password);

			Jspar->cookie = wsid;

			resultat = Jspar->currentUserBelongsTo(inGroupName->Idgroup,"" );
			
		}
		return resultat;
	}


	bool User::IsLoggedIn(const ISession* inSession)
	{


		bool resultat = false;
		
		Jsonparser *Jspar;
		Jspar=new Jsonparser(this->GetDirectory()->Get_Url_Wakanda(), this->GetDirectory()->Get_Url_Wakanda());
		
		if (inSession->cookies == "")return false;
		
		Jspar->cookie = inSession->cookies;
		
		vector<string> v1= Jspar->currentuser();
		
		if (v1[0] == this->Username)
		{
			
			return true;
		}

			
		
		return false;
		
		
	}
}