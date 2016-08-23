/*
@file   IUser.h
@abstract   define the user object interface
*/

#ifndef User_H
#define User_H
#include<string>
#include<vector>
#include"IUser.h"
#include"IDirectory.h"
using namespace std;

namespace WaDirectory
{

	class Directory;
	class Session;
	class Group;
	class User 
	{
	private :
		
		Directory *Pt_Directory = NULL;

	public:
		string Username, FullName, Id,Password;
		User();
		User(string Username, string FullName, string Id,string Password);
		User::~User();
		Directory* GetDirectory()   const ;

		void GetName(std::string& outName) ;

		bool BelongsToGroup(const std::string& inGroupName) ;

		bool    BelongsToGroup(const Group* inGroupName)  ;

		bool    IsLoggedIn(const Session* inSession) ;
		
		void Set_Directory(Directory* Pt_Directory);

	};

}
#endif