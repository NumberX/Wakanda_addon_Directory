#include "Directory.h"
#include"Session.h"
#include<vector>
#include"Jsonparser.h"
#include"XMLparser.h"
#include"Group.h"
#include"User.h"
using namespace WaDirectory_data;
namespace WaDirectory
{

	Directory::Directory()
	{
	}


	Directory::~Directory()
	{
	}
	Session*    Directory::LogIn(const std::string& inUser, const std::string& inPassword)
	{
		Session* session;// = new Session();
		Jsonparser Jspar;
		string wsid=Jspar.login(inUser, inPassword);
		if (wsid.length() > 0)
		{
			session = new Session();
			session->wsid = wsid;
			session->cookies = Jspar.cookie;
			return session;
		}
		return nullptr;
	
	
	
	
	}

	void         Directory::GetGroupNames(std::vector<std::string>& outGroupName)
	{
		XMLparser prt;
		outGroupName.clear();
		outGroupName = prt.ListGroup();
	
	
	}

	Group*      Directory::GetGroup(const std::string& inGroupName){ 
		XMLparser prt;
		Group *grp;
		if (prt.NameGrouoById(inGroupName).length()>0)
		grp = new Group(inGroupName);
		return grp;
	
	
	
	}

	User*       Directory::GetUser(const std::string& inUserName){ 
		XMLparser prt;
		User *grp;
		grp = new User(inUserName, prt.NameUserById(inUserName, "name"), prt.NameUserById(inUserName, "fullname"), "");
		return grp;


	}

	bool         Directory::LogOut(const Session* inSession){ 

		// = new Session();
		Jsonparser Jspar;
		Jspar.cookie = inSession->cookies;
		bool resultat = Jspar.Logout();
		
		return resultat;
		
	
	}

	Session*    Directory::GetSession(const std::string& inSessionID){ 

		Session* session;// = new Session();
		
			session = new Session();
			
			session->cookies = inSessionID;
			return session;
		
		
		 }

	bool         Directory::UserBelongTo(const Session* inSession, const std::string& inGroupID){
		
		Jsonparser Jspar;
		Jspar.cookie = inSession->cookies;
		bool resultat = Jspar.currentUserBelongsTo(inGroupID,"");

		return resultat;


		
	
	
	}

	bool         Directory::UserBelongTo(const User* inUser, const std::string& inGroupID)
	{ 
		XMLparser prt;
		return prt.UserBelongGroup(inUser->Id, inGroupID);
		
	
	}

	bool         Directory::UserBelongTo(const User* inUser, const Group* inGroupID){ 
		
		XMLparser prt;
		return prt.UserBelongGroup(inUser->Id, inGroupID->Idgroup);

			
	
	}
}