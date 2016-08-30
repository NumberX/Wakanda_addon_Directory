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
	class User :public IUser
	{
	private :
		
		

	public:
		
		User();
		User(string Username, string FullName, string Id,string Password);
		 ~User();
		 IDirectory* GetDirectory()   ;

		 void GetName(std::string& outName) ;

		 bool BelongsToGroup(const std::string& inGroupName);

		 bool    BelongsToGroup(const IGroup* inGroupName);

		 bool    IsLoggedIn(const ISession* inSession);
		
		 void Set_Directory(IDirectory* Pt_Directory);



	};

}
#endif