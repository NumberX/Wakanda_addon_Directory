/*
@file IDirectory.h
@abstract Directory interface definition
*/

#ifndef Directory_H
#define Directory_H
#include"IDirectory.h"
#include"ManageSession.h"
#include"SessionLog.h"
#include<string>
#include<vector>
using namespace std;


namespace WaDirectory_Data
{
	class Group;
	class User;
	class Session;


	class Directory:public IDirectory
	{
	public:

		

		Directory();

		Directory(std::string Url_Wakanda, std::string Url_Directory);

		 ~Directory();

		 ISession*    LogIn(const std::string& inUser, const std::string& inPassword);

		 void         GetGroupNames(std::vector<std::string>& outGroupName);
		
		 void        GetGroupId(std::vector<std::string>& outGroupName);

		 void        GetUsersId(std::vector<std::string>& outGroupName);
		 
		 IGroup*      GetGroup(const std::string& inGroupName);

		 IUser*       GetUser(const std::string& inUserName, const std::string& Password);

		 IUser*       GetUserById(const std::string& inUserId);

		 bool         LogOut(const ISession* inSession);

		 ISession*    GetSession(const std::string& inSessionID);

		 bool         UserBelongTo(const ISession* inSession, const std::string& inGroupID);

		 bool         UserBelongTo(const IUser* inUser, const std::string& inGroupID);

		 bool         UserBelongTo(const IUser* inUser, const IGroup* inGroupID);
		
		 std::string	 Get_Url_Wakanda();

		 std::string  Get_Url_Directory();
		
	     void		 Set_Url_Wakanda(std::string Url_Wakanda);
		
		 void		 Set_Url_Directory(std::string Url_Directory);

		 bool         Existbyname(string name);

		 bool         Isvalid(string Username, string Password);

		 vector<SessionLog> loadfile();

		
	
	private :
		

	};
}
#endif