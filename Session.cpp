#include "Session.h"
#include "Directory.h"
#include"User.h"
#include"IUser.h"
#include"Jsonparser.h"
#include<iostream>
using namespace std;
using namespace WaDirectory_data;
namespace WaDirectory
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

			

		}
		return pt;
	}


	bool Session::IsValid()
	{
		
		Jsonparser *json;
		json = new Jsonparser(this->GetDirectory()->Get_Url_Wakanda(), this->GetDirectory()->Get_Url_Directory());
		json->cookie = this->cookies;
		
		vector<string>Id = json->currentuser();
		
		if (Id.size() > 1)
			return true;
		return false;
	}


	void Session::LogOut()
	{
		Jsonparser *json;
		json =new Jsonparser (this->GetDirectory()->Get_Url_Wakanda(), this->GetDirectory()->Get_Url_Directory());
		json->cookie = this->cookies;
		
		json->Logout();


		this->Pt_Directory->List.RemoveBycookies(this->cookies);

		std::cout << "List After Logout" << endl;

		this->Pt_Directory->List.Affiche();
	}


	IDirectory* Session::GetDirectory() 
	{
		return this->Pt_Directory;
	}


	void Session::GetWASID(std::string& outWASID) 
	{
		outWASID = this->cookies;
	}
}