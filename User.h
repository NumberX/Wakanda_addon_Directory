/*
@file   IUser.h
@abstract   define the user object interface
*/

#pragma once
#include<string>
#include<vector>
using namespace std;

namespace WaDirectory
{

	class Directory;
	class Session;
	class Group;
	class User
	{
	private :
		
	public:
		string Username, FullName, Id,Password;
		User::User();
		User(string Username, string FullName, string Id,string Password);
		User::~User();
		Directory* GetDirectory()   const ;

		void GetName(std::string& outName) ;

		bool BelongsToGroup(const std::string& inGroupName) ;

		bool    BelongsToGroup(const Group* inGroupName)  ;

		bool    IsLoggedIn(const Session* inSession) ;


	};

}