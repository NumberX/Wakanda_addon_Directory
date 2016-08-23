/*
@file IDirectory.h
@abstract Directory interface definition
*/

#ifndef Directory_H
#define Directory_H
#include"IDirectory.h"
#include<string>
#include<vector>
using namespace std;


namespace WaDirectory
{
	class Group;
	class User;
	class Session;

	class Directory
	{
	public:

		Directory();

		Directory(std::string Url_Wakanda, std::string Url_Directory);

		~Directory();

		Session*    LogIn(const std::string& inUser, const std::string& inPassword); 

		void         GetGroupNames(std::vector<std::string>& outGroupName) ;

		Group*      GetGroup(const std::string& inGroupName) ;

		User*       GetUser(const std::string& inUserName) ;

		bool         LogOut(const Session* inSession);

		Session*    GetSession(const std::string& inSessionID) ;

		bool         UserBelongTo(const Session* inSession, const std::string& inGroupID) ;

		bool         UserBelongTo(const User* inUser, const std::string& inGroupID) ;

		bool         UserBelongTo(const User* inUser, const Group* inGroupID) ;
		
		std::string	 Get_Url_Wakanda();

		std::string  Get_Url_Directory();
		
		void		 Set_Url_Wakanda(std::string Url_Wakanda);
		
		void		 Set_Url_Directory(std::string Url_Directory);
	
	private :
		std::string Url_Wakanda, Url_Directory;

	};
}
#endif