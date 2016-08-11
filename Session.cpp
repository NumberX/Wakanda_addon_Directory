#include "Session.h"
#include"User.h"
#include"Jsonparser.h"
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


	User* Session::GetUser()
	{
		

		Jsonparser json;
		json.cookie = this->cookies;
		vector<string>Id =json.currentuser();
		User *pt;
		if (Id.size()>1)
		{ 
		pt = new User(Id[0], Id[1], Id[2],"");
		return pt;
		}
		return nullptr;
	}


	bool Session::IsValid()
	{
		Jsonparser json;
		json.cookie = this->cookies;
		vector<string>Id = json.currentuser();
		
		if (Id.size() > 1)
			return true;
		return false;
	}


	void Session::LogOut()
	{
		Jsonparser json;
		json.cookie = this->cookies;
		json.Logout();
	}


	Directory* Session::GetDirectory() const
	{
		return nullptr;
	}


	void Session::GetWASID(std::string& outWASID) const
	{
		outWASID = this->cookies;
	}
}