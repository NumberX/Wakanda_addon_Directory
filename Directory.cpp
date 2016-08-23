#include "Directory.h"
#include"Session.h"
#include<vector>
#include"Jsonparser.h"
#include"XMLparser.h"
#include"Group.h"
#include"User.h"
#include<iostream>
using namespace std;
using namespace WaDirectory_data;
namespace WaDirectory
{

	Directory::Directory() 
	{
	}


	Directory::Directory(std::string Url_Wakanda, std::string Url_Directory)
	{
		this->Url_Wakanda = Url_Wakanda;
		this->Url_Directory = Url_Directory;

	}


	Directory::~Directory()
	{
	}
	Session*    Directory::LogIn(const std::string& inUser, const std::string& inPassword)
	{
		Session* session=NULL;

		Jsonparser Jspar(this->Url_Wakanda,this->Url_Directory);
		
		string wsid=Jspar.login(inUser, inPassword);
		
		if (wsid.length() > 0)
		{
		
			session = new Session();
			
			session->wsid = wsid;
			
			session->cookies = Jspar.cookie;
			

		 }
		return session;
	
	
	
	
	}


	std::string	 Directory::Get_Url_Wakanda(){
	
		return this->Url_Wakanda;
	}

	std::string  Directory::Get_Url_Directory()
	{

		return this->Url_Directory;

	}

	void		 Directory::Set_Url_Wakanda(std::string Url_Wakanda)
	{

		this->Url_Wakanda = Url_Wakanda;
	}

	void		 Directory::Set_Url_Directory(std::string Url_Directory)
	{
	
		this->Url_Directory = Url_Directory;
	}

	void         Directory::GetGroupNames(std::vector<std::string>& outGroupName)
	{
		XMLparser PtparseurXml(this->Get_Url_Directory());
	
		outGroupName.clear();
		
		outGroupName = PtparseurXml.ListGroup();
	
	
	}

	Group*      Directory::GetGroup(const std::string& inGroupName){ 
		
		XMLparser PtparseurXml(this->Get_Url_Directory());
		
		Group *PtGroup=NULL;
		
		if (PtparseurXml.NameGrouoById(inGroupName).length()>0)
		
			PtGroup = new Group(inGroupName);
		
		return PtGroup;
	
	
	
	}

	User*       Directory::GetUser(const std::string& inUserName){ 

		XMLparser PtparseurXml(this->Get_Url_Directory());

		User *PtUser;

		PtUser = new User(inUserName, PtparseurXml.NameUserById(inUserName, "name"), PtparseurXml.NameUserById(inUserName, "fullname"), "");

		return PtUser;


	}

	bool         Directory::LogOut(const Session* inSession){

		Jsonparser Jspar(this->Url_Wakanda, this->Url_Directory);
		
		Jspar.cookie = inSession->cookies;
		
		bool resultat = Jspar.Logout();
		
		return resultat;
		
	
	}

	Session*    Directory::GetSession(const std::string& inSessionID){ 

		    Session* session;
		
			session = new Session();
			
			session->cookies = inSessionID;
			return session;
		
		
		 }

	bool         Directory::UserBelongTo(const Session* inSession, const std::string& inGroupID){
		
		Jsonparser Jspar(this->Url_Wakanda, this->Url_Directory);

		Jspar.cookie = inSession->cookies;
		
		bool resultat = Jspar.currentUserBelongsTo(inGroupID,"");

		return resultat;


		
	
	
	}

	bool         Directory::UserBelongTo(const User* inUser, const std::string& inGroupID)
	{ 
		XMLparser PtparseurXml(this->Get_Url_Directory());

		return PtparseurXml.UserBelongGroup(inUser->Id, inGroupID);
		
	
	}

	bool         Directory::UserBelongTo(const User* inUser, const Group* inGroupID){ 
		
		XMLparser PtparseurXml(this->Get_Url_Directory());
		
		return PtparseurXml.UserBelongGroup(inUser->Id, inGroupID->Idgroup);

			
	
	}
}