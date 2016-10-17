#include "Session.h"
#include "Directory.h"
#include"User.h"
#include"IUser.h"
#include"Jsonparser.h"
#include<iostream>
using namespace std;
namespace WaDirectory_Data
{


	Session::Session()
	{
	}
	Session::Session(string cookies)
	{
		this->cookies = cookies;
	}

	Session::~Session()
	{
	}

	void  Session::Set_Directory(IDirectory* Pt_Directory)
	{
		this->Pt_Directory = Pt_Directory;
	
	}
	IUser* Session::GetUser()
	{
		
		
		Jsonparser *json;
			json=	new Jsonparser(this->GetDirectory()->Get_Url_Wakanda(), this->GetDirectory()->Get_Url_Directory());

		json->cookie = this->cookies;
		
		vector<string>Id =json->currentuser();

		
		User *pt=NULL;
		
		if (Id.size()>1)
		{ 

			pt = new User(Id[0], Id[1], Id[2],"");

			this->Pt_Directory->List.UpdateBycookies(this->cookies, json->Ttl);

		}

		delete json;

		return pt;
	}


	bool Session::IsValid()
	{
		
		Jsonparser *json;
		json = new Jsonparser(this->GetDirectory()->Get_Url_Wakanda(), this->GetDirectory()->Get_Url_Directory());
		json->cookie = this->cookies;
		
		vector<string>Id = json->currentuser();
		
		if (Id.size() > 1)
		{ 
		

			this->Pt_Directory->List.UpdateBycookies(this->cookies, json->Ttl);

			delete json;

			return true;

		}

		delete json;

		return false;
	}


	void Session::LogOut()
	{
		Jsonparser *json;
		json =new Jsonparser (this->GetDirectory()->Get_Url_Wakanda(), this->GetDirectory()->Get_Url_Directory());
		json->cookie = this->cookies;
		
		json->Logout();


		this->Pt_Directory->List.RemoveBycookies(this->cookies);

		delete json;
	}


	IDirectory* Session::GetDirectory() 
	{
		return this->Pt_Directory;
	}


	void Session::GetWASID(std::string& outWASID) 
	{
		outWASID = this->cookies;
	}

	void Session::GetWASID1(std::string& outWASID)
	{
		 

		string sub = "";

		int pos = static_cast<int>(this->cookies.find("WASID	"));

		sub = this->cookies.substr(pos + 6);

		outWASID=sub;
	}
}