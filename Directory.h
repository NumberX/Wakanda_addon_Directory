/*
@file IDirectory.h
@abstract Directory interface definition
*/

#pragma once

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
		~Directory();
	
		Session*    LogIn(const std::string& inUser, const std::string& inPassword) ;

		void         GetGroupNames(std::vector<std::string>& outGroupName) ;

		Group*      GetGroup(const std::string& inGroupName) ;

		User*       GetUser(const std::string& inUserName) ;

		bool         LogOut(const string inSession) ;

		Session*    GetSession(const std::string& inSessionID) ;

		bool         UserBelongTo(const Session* inSession, const std::string& inGroupID) ;

		bool         UserBelongTo(const User* inUser, const std::string& inGroupID) ;

		bool         UserBelongTo(const User* inUser, const Group* inGroupID) ;

	};
}