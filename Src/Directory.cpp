#include "Directory.h"
#include"Session.h"
#include<vector>
#include"Jsonparser.h"
#include"XMLparser.h"
#include"Group.h"
#include"User.h"
#include<iostream>
using namespace std;
namespace WaDirectory_Data
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


	bool Directory::Existbyname(string name)
	{
		XMLparser *PtparseurXml;

		PtparseurXml = new XMLparser(this->Get_Url_Directory());


		if (PtparseurXml->ExistUserByname(name, "name"))
		{
			 return true;

		}
				return false;
	}

	bool Directory::Isvalid(string Username,string Password)
	{
		Jsonparser *Jspar;

		Jspar = new Jsonparser(this->Url_Wakanda, this->Url_Directory);
		string wsid = Jspar->login(Username, Password);

		Jspar->Logout();

		if (wsid.length() > 0)
		{

			return true;

		}
	
		return false;
	}
	ISession*    Directory::LogIn(const std::string& inUser, const std::string& inPassword)
	{
		Session* session=NULL;

		Jsonparser *Jspar;

		Jspar = new Jsonparser(this->Url_Wakanda, this->Url_Directory);
		string wsid=Jspar->login(inUser, inPassword);

		
		if (wsid.length() > 0)
		{
		
			session = new Session();
			
			session->wsid = wsid;
			
			session->cookies = wsid;

			IUser* UserId = GetUser(inUser, inPassword);

			if (List.FindByUserId(UserId->Id) == true)
			{
				string cookies = List.Getcookies(UserId->Id);

				List.Remove(UserId->Id);

				ISession* inSession = new Session(cookies);

				LogOut(inSession);
			}
			
			List.Register(UserId->Id, wsid, UserId->Username);

			std::cout << "List currents Users" << endl;

			List.Affiche();

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
		XMLparser *PtparseurXml;
	
		PtparseurXml = new XMLparser(this->Get_Url_Directory());
	
		outGroupName.clear();
		
		outGroupName = PtparseurXml->ListGroup();
	
	
	}
	void         Directory::GetGroupId(std::vector<std::string>& outGroupName)
	{
		XMLparser *PtparseurXml;

		PtparseurXml = new XMLparser(this->Get_Url_Directory());

		outGroupName.clear();

		outGroupName = PtparseurXml->ListGroupId();


	}

	IGroup*      Directory::GetGroup(const std::string& inGroupName){ 
		
		XMLparser *PtparseurXml;

		PtparseurXml = new XMLparser(this->Get_Url_Directory());

		IGroup *PtGroup=NULL;
		
		if (PtparseurXml->NameGrouoById(inGroupName).length()>0)
		
			PtGroup = new Group(inGroupName);
		
		return PtGroup;
	
	
	
	}

	IUser*       Directory::GetUser(const std::string& inUserName, const std::string& Password){

		XMLparser *PtparseurXml;

		PtparseurXml = new XMLparser(this->Get_Url_Directory());

		User *PtUser=NULL;

		if (PtparseurXml->ExistUserByname(inUserName, "name"))
		{
			string Id = PtparseurXml->UserIdByname(inUserName);
			PtUser = new User(inUserName, PtparseurXml->NameUserById(Id,"fullname"),Id , Password);
		}
		return PtUser;


	}

	bool         Directory::LogOut(const ISession* inSession){

		Jsonparser *Jspar;
		Jspar = new Jsonparser(this->Url_Wakanda, this->Url_Directory);
		Jspar->cookie = inSession->cookies;
		
		bool resultat = Jspar->Logout();

		this->List.RemoveBycookies(inSession->cookies);

		std::cout << "List After Logout" << endl;

		this->List.Affiche();
		
		return resultat;
		
	
	}

	ISession*    Directory::GetSession(const std::string& inSessionID){ 

		    Session* session;
		
			session = new Session();
			
			session->cookies = inSessionID;
			return session;
		
		
		 }

	bool         Directory::UserBelongTo(const ISession* inSession, const std::string& inGroupID){
		
		Jsonparser* Jspar;
		Jspar = new Jsonparser(this->Url_Wakanda, this->Url_Directory);

		Jspar->cookie = inSession->cookies;
		
		bool resultat = Jspar->currentUserBelongsTo(inGroupID,"");

		return resultat;
	
	}

	bool         Directory::UserBelongTo(const IUser* inUser, const std::string& inGroupID)
	{ 

		Jsonparser*PTJasper;

		PTJasper = new Jsonparser(this->Url_Wakanda, this->Url_Directory);
		
		ISession*PtSession=this->LogIn(inUser->Username, inUser->Password);

		PtSession->GetWASID(PTJasper->cookie);

		bool resultat=PTJasper->currentUserBelongsTo(inGroupID, "");
		
		PTJasper->Logout();
		
		return resultat;
	
	}

	bool         Directory::UserBelongTo(const IUser* inUser, const IGroup* inGroupID){ 
		
		XMLparser PtparseurXml(this->Get_Url_Directory());
		
		return PtparseurXml.UserBelongGroup(inUser->Id, inGroupID->Idgroup);

			
	
	}
}